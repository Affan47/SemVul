process_state_close_lc(struct nfcmrvl_private *priv,
				  struct sk_buff *skb)
{
	if (sizeof(nci_pattern_core_conn_close_rsp) != skb->len ||
	    memcmp(skb->data, nci_pattern_core_conn_close_rsp, skb->len))
		return -EINVAL;

	priv->fw_dnld.state = STATE_BOOT;
	nci_send_cmd(priv->ndev, NCI_OP_PROPRIETARY_BOOT_CMD, 0, NULL);
	return 0;
}
