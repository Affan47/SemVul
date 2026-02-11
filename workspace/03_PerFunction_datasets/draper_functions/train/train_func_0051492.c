isert_set_sig_attrs(struct se_cmd *se_cmd, struct ib_sig_attrs *sig_attrs)
{
	switch (se_cmd->prot_op) {
	case TARGET_PROT_DIN_INSERT:
	case TARGET_PROT_DOUT_STRIP:
		sig_attrs->mem.sig_type = IB_SIG_TYPE_NONE;
		isert_set_dif_domain(se_cmd, sig_attrs, &sig_attrs->wire);
		break;
	case TARGET_PROT_DOUT_INSERT:
	case TARGET_PROT_DIN_STRIP:
		sig_attrs->wire.sig_type = IB_SIG_TYPE_NONE;
		isert_set_dif_domain(se_cmd, sig_attrs, &sig_attrs->mem);
		break;
	case TARGET_PROT_DIN_PASS:
	case TARGET_PROT_DOUT_PASS:
		isert_set_dif_domain(se_cmd, sig_attrs, &sig_attrs->wire);
		isert_set_dif_domain(se_cmd, sig_attrs, &sig_attrs->mem);
		break;
	default:
		isert_err("Unsupported PI operation %d\n", se_cmd->prot_op);
		return -EINVAL;
	}

	return 0;
}
