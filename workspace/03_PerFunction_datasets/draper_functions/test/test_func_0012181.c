ath10k_wmi_op_gen_pdev_set_param(struct ath10k *ar, u32 id, u32 value)
{
	struct wmi_pdev_set_param_cmd *cmd;
	struct sk_buff *skb;

	if (id == WMI_PDEV_PARAM_UNSUPPORTED) {
		ath10k_warn(ar, "pdev param %d not supported by firmware\n",
			    id);
		return ERR_PTR(-EOPNOTSUPP);
	}

	skb = ath10k_wmi_alloc_skb(ar, sizeof(*cmd));
	if (!skb)
		return ERR_PTR(-ENOMEM);

	cmd = (struct wmi_pdev_set_param_cmd *)skb->data;
	cmd->param_id    = __cpu_to_le32(id);
	cmd->param_value = __cpu_to_le32(value);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi pdev set param %d value %d\n",
		   id, value);
	return skb;
}
