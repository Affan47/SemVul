ath10k_wmi_op_gen_pdev_set_wmm(struct ath10k *ar,
			       const struct wmi_wmm_params_all_arg *arg)
{
	struct wmi_pdev_set_wmm_params *cmd;
	struct sk_buff *skb;

	skb = ath10k_wmi_alloc_skb(ar, sizeof(*cmd));
	if (!skb)
		return ERR_PTR(-ENOMEM);

	cmd = (struct wmi_pdev_set_wmm_params *)skb->data;
	ath10k_wmi_set_wmm_param(&cmd->ac_be, &arg->ac_be);
	ath10k_wmi_set_wmm_param(&cmd->ac_bk, &arg->ac_bk);
	ath10k_wmi_set_wmm_param(&cmd->ac_vi, &arg->ac_vi);
	ath10k_wmi_set_wmm_param(&cmd->ac_vo, &arg->ac_vo);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi pdev set wmm params\n");
	return skb;
}
