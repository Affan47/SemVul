qlafx00_rescan_isp(scsi_qla_host_t *vha)
{
	uint32_t status = QLA_FUNCTION_FAILED;
	struct qla_hw_data *ha = vha->hw;
	struct device_reg_fx00 __iomem *reg = &ha->iobase->ispfx00;
	uint32_t aenmbx7;

	qla2x00_request_irqs(ha, ha->rsp_q_map[0]);

	aenmbx7 = RD_REG_DWORD(&reg->aenmailbox7);
	ha->mbx_intr_code = MSW(aenmbx7);
	ha->rqstq_intr_code = LSW(aenmbx7);
	ha->req_que_off = RD_REG_DWORD(&reg->aenmailbox1);
	ha->rsp_que_off = RD_REG_DWORD(&reg->aenmailbox3);
	ha->req_que_len = RD_REG_DWORD(&reg->aenmailbox5);
	ha->rsp_que_len = RD_REG_DWORD(&reg->aenmailbox6);

	ql_dbg(ql_dbg_disc, vha, 0x2094,
	    "fw returned mbx_intr_code: 0x%x, rqstq_intr_code: 0x%x "
	    " Req que offset 0x%x Rsp que offset 0x%x\n",
	    ha->mbx_intr_code, ha->rqstq_intr_code,
	    ha->req_que_off, ha->rsp_que_len);


	QLAFX00_CLR_INTR_REG(ha, QLAFX00_HST_INT_STS_BITS);

	status = qla2x00_init_rings(vha);
	if (!status) {
		vha->flags.online = 1;


		if ((vha->device_flags & DFLG_NO_CABLE))
			status = 0;

		if (qlafx00_fx_disc(vha,
		    &vha->hw->mr.fcport, FXDISC_REG_HOST_INFO))
			ql_dbg(ql_dbg_disc, vha, 0x2095,
			    "failed to register host info\n");
	}
	scsi_unblock_requests(vha->host);
	return status;
}
