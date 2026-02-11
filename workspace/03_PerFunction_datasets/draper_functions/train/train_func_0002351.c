ath10k_wmi_op_gen_peer_create(struct ath10k *ar, u32 vdev_id,
			      const u8 peer_addr[ETH_ALEN],
			      enum wmi_peer_type peer_type)
{
	struct wmi_peer_create_cmd *cmd;
	struct sk_buff *skb;

	skb = ath10k_wmi_alloc_skb(ar, sizeof(*cmd));
	if (!skb)
		return ERR_PTR(-ENOMEM);

	cmd = (struct wmi_peer_create_cmd *)skb->data;
	cmd->vdev_id = __cpu_to_le32(vdev_id);
	ether_addr_copy(cmd->peer_macaddr.addr, peer_addr);

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi peer create vdev_id %d peer_addr %pM\n",
		   vdev_id, peer_addr);
	return skb;
}
