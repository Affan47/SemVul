qla24xx_msix_default(int irq, void *dev_id)
{
	scsi_qla_host_t	*vha;
	struct qla_hw_data *ha;
	struct rsp_que *rsp;
	struct device_reg_24xx __iomem *reg;
	int		status;
	uint32_t	stat;
	uint32_t	hccr;
	uint16_t	mb[8];
	unsigned long flags;

	rsp = (struct rsp_que *) dev_id;
	if (!rsp) {
		ql_log(ql_log_info, NULL, 0x505c,
		    "%s: NULL response queue pointer.\n", __func__);
		return IRQ_NONE;
	}
	ha = rsp->hw;
	reg = &ha->iobase->isp24;
	status = 0;

	spin_lock_irqsave(&ha->hardware_lock, flags);
	vha = pci_get_drvdata(ha->pdev);
	do {
		stat = RD_REG_DWORD(&reg->host_status);
		if (qla2x00_check_reg32_for_disconnect(vha, stat))
			break;
		if (stat & HSRX_RISC_PAUSED) {
			if (unlikely(pci_channel_offline(ha->pdev)))
				break;

			hccr = RD_REG_DWORD(&reg->hccr);

			ql_log(ql_log_info, vha, 0x5050,
			    "RISC paused -- HCCR=%x, Dumping firmware.\n",
			    hccr);

			qla2xxx_check_risc_status(vha);

			ha->isp_ops->fw_dump(vha, 1);
			set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
			break;
		} else if ((stat & HSRX_RISC_INT) == 0)
			break;

		switch (stat & 0xff) {
		case INTR_ROM_MB_SUCCESS:
		case INTR_ROM_MB_FAILED:
		case INTR_MB_SUCCESS:
		case INTR_MB_FAILED:
			qla24xx_mbx_completion(vha, MSW(stat));
			status |= MBX_INTERRUPT;

			break;
		case INTR_ASYNC_EVENT:
			mb[0] = MSW(stat);
			mb[1] = RD_REG_WORD(&reg->mailbox1);
			mb[2] = RD_REG_WORD(&reg->mailbox2);
			mb[3] = RD_REG_WORD(&reg->mailbox3);
			qla2x00_async_event(vha, rsp, mb);
			break;
		case INTR_RSP_QUE_UPDATE:
		case INTR_RSP_QUE_UPDATE_83XX:
			qla24xx_process_response_queue(vha, rsp);
			break;
		case INTR_ATIO_QUE_UPDATE:{
			unsigned long flags2;
			spin_lock_irqsave(&ha->tgt.atio_lock, flags2);
			qlt_24xx_process_atio_queue(vha, 1);
			spin_unlock_irqrestore(&ha->tgt.atio_lock, flags2);
			break;
		}
		case INTR_ATIO_RSP_QUE_UPDATE: {
			unsigned long flags2;
			spin_lock_irqsave(&ha->tgt.atio_lock, flags2);
			qlt_24xx_process_atio_queue(vha, 1);
			spin_unlock_irqrestore(&ha->tgt.atio_lock, flags2);

			qla24xx_process_response_queue(vha, rsp);
			break;
		}
		default:
			ql_dbg(ql_dbg_async, vha, 0x5051,
			    "Unrecognized interrupt type (%d).\n", stat & 0xff);
			break;
		}
		WRT_REG_DWORD(&reg->hccr, HCCRX_CLR_RISC_INT);
	} while (0);
	qla2x00_handle_mbx_completion(ha, status);
	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	return IRQ_HANDLED;
}
