fc_seq_els_rsp_send(struct fc_frame *fp, enum fc_els_cmd els_cmd,
				struct fc_seq_els_data *els_data)
{
	switch (els_cmd) {
	case ELS_LS_RJT:
		fc_seq_ls_rjt(fp, els_data->reason, els_data->explan);
		break;
	case ELS_LS_ACC:
		fc_seq_ls_acc(fp);
		break;
	case ELS_RRQ:
		fc_exch_els_rrq(fp);
		break;
	case ELS_REC:
		fc_exch_els_rec(fp);
		break;
	default:
		FC_LPORT_DBG(fr_dev(fp), "Invalid ELS CMD:%x\n", els_cmd);
	}
}
