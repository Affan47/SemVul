st21nfca_hci_enable_se(struct nfc_hci_dev *hdev, u32 se_idx)
{
	int r;


	r = st21nfca_hci_control_se(hdev, se_idx, ST21NFCA_SE_MODE_ON);
	if (r == ST21NFCA_ESE_HOST_ID) {
		st21nfca_se_get_atr(hdev);
		r = nfc_hci_send_event(hdev, ST21NFCA_APDU_READER_GATE,
				ST21NFCA_EVT_SE_SOFT_RESET, NULL, 0);
		if (r < 0)
			return r;
	} else if (r < 0) {


		nfc_remove_se(hdev->ndev, se_idx);
		return r;
	}

	return 0;
}
