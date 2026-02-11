qla24xx_process_response_queue(struct scsi_qla_host *vha,
	struct rsp_que *rsp)
{
	struct sts_entry_24xx *pkt;
	struct qla_hw_data *ha = vha->hw;

	if (!vha->flags.online)
		return;

	if (rsp->msix && (rsp->msix->cpuid != smp_processor_id())) {


		rsp->msix->cpuid = smp_processor_id();
		ha->tgt.rspq_vector_cpuid = rsp->msix->cpuid;
	}

	while (rsp->ring_ptr->signature != RESPONSE_PROCESSED) {
		pkt = (struct sts_entry_24xx *)rsp->ring_ptr;

		rsp->ring_index++;
		if (rsp->ring_index == rsp->length) {
			rsp->ring_index = 0;
			rsp->ring_ptr = rsp->ring;
		} else {
			rsp->ring_ptr++;
		}

		if (pkt->entry_status != 0) {
			qla2x00_error_entry(vha, rsp, (sts_entry_t *) pkt);

			if (qlt_24xx_process_response_error(vha, pkt))
				goto process_err;

			((response_t *)pkt)->signature = RESPONSE_PROCESSED;
			wmb();
			continue;
		}
process_err:

		switch (pkt->entry_type) {
		case STATUS_TYPE:
			qla2x00_status_entry(vha, rsp, pkt);
			break;
		case STATUS_CONT_TYPE:
			qla2x00_status_cont_entry(rsp, (sts_cont_entry_t *)pkt);
			break;
		case VP_RPT_ID_IOCB_TYPE:
			qla24xx_report_id_acquisition(vha,
			    (struct vp_rpt_id_entry_24xx *)pkt);
			break;
		case LOGINOUT_PORT_IOCB_TYPE:
			qla24xx_logio_entry(vha, rsp->req,
			    (struct logio_entry_24xx *)pkt);
			break;
		case CT_IOCB_TYPE:
			qla24xx_els_ct_entry(vha, rsp->req, pkt, CT_IOCB_TYPE);
			break;
		case ELS_IOCB_TYPE:
			qla24xx_els_ct_entry(vha, rsp->req, pkt, ELS_IOCB_TYPE);
			break;
		case ABTS_RECV_24XX:
			if (IS_QLA83XX(ha) || IS_QLA27XX(ha)) {

				qlt_handle_abts_recv(vha, (response_t *)pkt);
				break;
			} else {

				qlt_24xx_process_atio_queue(vha, 1);
			}
		case ABTS_RESP_24XX:
		case CTIO_TYPE7:
		case NOTIFY_ACK_TYPE:
		case CTIO_CRC2:
			qlt_response_pkt_all_vps(vha, (response_t *)pkt);
			break;
		case MARKER_TYPE:


			break;
		case ABORT_IOCB_TYPE:
			qla24xx_abort_iocb_entry(vha, rsp->req,
			    (struct abort_entry_24xx *)pkt);
			break;
		default:

			ql_dbg(ql_dbg_async, vha, 0x5042,
			    "Received unknown response pkt type %x "
			    "entry status=%x.\n",
			    pkt->entry_type, pkt->entry_status);
			break;
		}
		((response_t *)pkt)->signature = RESPONSE_PROCESSED;
		wmb();
	}


	if (IS_P3P_TYPE(ha)) {
		struct device_reg_82xx __iomem *reg = &ha->iobase->isp82;
		WRT_REG_DWORD(&reg->rsp_q_out[0], rsp->ring_index);
	} else
		WRT_REG_DWORD(rsp->rsp_q_out, rsp->ring_index);
}
