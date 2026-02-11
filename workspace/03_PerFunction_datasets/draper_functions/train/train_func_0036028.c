st21nfca_im_send_atr_req(struct nfc_hci_dev *hdev, u8 *gb, size_t gb_len)
{
	struct sk_buff *skb;
	struct st21nfca_hci_info *info = nfc_hci_get_clientdata(hdev);
	struct st21nfca_atr_req *atr_req;
	struct nfc_target *target;
	uint size;

	info->dep_info.to = ST21NFCA_DEFAULT_TIMEOUT;
	size = ST21NFCA_ATR_REQ_MIN_SIZE + gb_len;
	if (size > ST21NFCA_ATR_REQ_MAX_SIZE) {
		PROTOCOL_ERR("14.6.1.1");
		return -EINVAL;
	}

	skb =
	    alloc_skb(sizeof(struct st21nfca_atr_req) + gb_len + 1, GFP_KERNEL);
	if (!skb)
		return -ENOMEM;

	skb_reserve(skb, 1);

	skb_put(skb, sizeof(struct st21nfca_atr_req));

	atr_req = (struct st21nfca_atr_req *)skb->data;
	memset(atr_req, 0, sizeof(struct st21nfca_atr_req));

	atr_req->cmd0 = ST21NFCA_NFCIP1_REQ;
	atr_req->cmd1 = ST21NFCA_NFCIP1_ATR_REQ;
	memset(atr_req->nfcid3, 0, NFC_NFCID3_MAXSIZE);
	target = hdev->ndev->targets;

	if (target->sensf_res_len > 0)
		memcpy(atr_req->nfcid3, target->sensf_res,
				target->sensf_res_len);
	else
		get_random_bytes(atr_req->nfcid3, NFC_NFCID3_MAXSIZE);

	atr_req->did = 0x0;

	atr_req->bsi = 0x00;
	atr_req->bri = 0x00;
	atr_req->ppi = ST21NFCA_LR_BITS_PAYLOAD_SIZE_254B;
	if (gb_len) {
		atr_req->ppi |= ST21NFCA_GB_BIT;
		memcpy(skb_put(skb, gb_len), gb, gb_len);
	}
	atr_req->length = sizeof(struct st21nfca_atr_req) + hdev->gb_len;

	*skb_push(skb, 1) = info->dep_info.to | 0x10;

	info->async_cb_type = ST21NFCA_CB_TYPE_READER_F;
	info->async_cb_context = info;
	info->async_cb = st21nfca_im_recv_atr_res_cb;
	info->dep_info.bri = atr_req->bri;
	info->dep_info.bsi = atr_req->bsi;
	info->dep_info.lri = ST21NFCA_PP2LRI(atr_req->ppi);

	return nfc_hci_send_cmd_async(hdev, ST21NFCA_RF_READER_F_GATE,
				ST21NFCA_WR_XCHG_DATA, skb->data,
				skb->len, info->async_cb, info);
}
