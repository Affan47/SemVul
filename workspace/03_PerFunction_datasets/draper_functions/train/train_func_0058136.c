st21nfca_tm_recv_atr_req(struct nfc_hci_dev *hdev,
				    struct sk_buff *skb)
{
	struct st21nfca_atr_req *atr_req;
	size_t gb_len;
	int r;

	skb_trim(skb, skb->len - 1);

	if (!skb->len) {
		r = -EIO;
		goto exit;
	}

	if (skb->len < ST21NFCA_ATR_REQ_MIN_SIZE) {
		r = -EPROTO;
		goto exit;
	}

	atr_req = (struct st21nfca_atr_req *)skb->data;

	if (atr_req->length < sizeof(struct st21nfca_atr_req)) {
		r = -EPROTO;
		goto exit;
	}

	r = st21nfca_tm_send_atr_res(hdev, atr_req);
	if (r)
		goto exit;

	gb_len = skb->len - sizeof(struct st21nfca_atr_req);

	r = nfc_tm_activated(hdev->ndev, NFC_PROTO_NFC_DEP_MASK,
			      NFC_COMM_PASSIVE, atr_req->gbi, gb_len);
	if (r)
		goto exit;

	r = 0;

exit:
	return r;
}
