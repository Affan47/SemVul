st21nfca_get_iso14443_3_uid(struct nfc_hci_dev *hdev, u8 *uid,
				       int *len)
{
	int r;
	struct sk_buff *uid_skb = NULL;

	r = nfc_hci_get_param(hdev, ST21NFCA_RF_READER_14443_3_A_GATE,
			      ST21NFCA_RF_READER_14443_3_A_UID, &uid_skb);
	if (r < 0)
		goto exit;

	if (uid_skb->len == 0 || uid_skb->len > NFC_NFCID1_MAXSIZE) {
		r = -EPROTO;
		goto exit;
	}

	memcpy(uid, uid_skb->data, uid_skb->len);
	*len = uid_skb->len;
exit:
	kfree_skb(uid_skb);
	return r;
}
