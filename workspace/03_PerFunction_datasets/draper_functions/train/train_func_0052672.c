ks_hw_init(struct ks_net *ks)
{
#define	MHEADER_SIZE	(sizeof(struct type_frame_head) * MAX_RECV_FRAMES)
	ks->promiscuous = 0;
	ks->all_mcast = 0;
	ks->mcast_lst_size = 0;

	ks->frame_head_info = devm_kmalloc(&ks->pdev->dev, MHEADER_SIZE,
					   GFP_KERNEL);
	if (!ks->frame_head_info)
		return false;

	ks_set_mac(ks, KS_DEFAULT_MAC_ADDRESS);
	return true;
}
