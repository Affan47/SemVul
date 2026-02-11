qla2x00_rsnn_nn(scsi_qla_host_t *vha)
{
	int		rval;
	struct qla_hw_data *ha = vha->hw;
	ms_iocb_entry_t	*ms_pkt;
	struct ct_sns_req	*ct_req;
	struct ct_sns_rsp	*ct_rsp;

	if (IS_QLA2100(ha) || IS_QLA2200(ha)) {
		ql_dbg(ql_dbg_disc, vha, 0x2050,
		    "RSNN_ID call unsupported on ISP2100/ISP2200.\n");
		return (QLA_SUCCESS);
	}


	ms_pkt = ha->isp_ops->prep_ms_iocb(vha, 0, RSNN_NN_RSP_SIZE);


	ct_req = qla2x00_prep_ct_req(ha->ct_sns, RSNN_NN_CMD,
	    RSNN_NN_RSP_SIZE);
	ct_rsp = &ha->ct_sns->p.rsp;


	memcpy(ct_req->req.rsnn_nn.node_name, vha->node_name, WWN_SIZE);


	qla2x00_get_sym_node_name(vha, ct_req->req.rsnn_nn.sym_node_name,
	    sizeof(ct_req->req.rsnn_nn.sym_node_name));


	ct_req->req.rsnn_nn.name_len =
	    (uint8_t)strlen(ct_req->req.rsnn_nn.sym_node_name);


	ms_pkt->req_bytecount =
	    cpu_to_le32(24 + 1 + ct_req->req.rsnn_nn.name_len);
	ms_pkt->dseg_req_length = ms_pkt->req_bytecount;


	rval = qla2x00_issue_iocb(vha, ha->ms_iocb, ha->ms_iocb_dma,
	    sizeof(ms_iocb_entry_t));
	if (rval != QLA_SUCCESS) {

		ql_dbg(ql_dbg_disc, vha, 0x2051,
		    "RSNN_NN issue IOCB failed (%d).\n", rval);
	} else if (qla2x00_chk_ms_status(vha, ms_pkt, ct_rsp, "RSNN_NN") !=
	    QLA_SUCCESS) {
		rval = QLA_FUNCTION_FAILED;
	} else {
		ql_dbg(ql_dbg_disc, vha, 0x2052,
		    "RSNN_NN exiting normally.\n");
	}

	return (rval);
}
