pn533_poll_dep_complete(struct pn533 *dev, void *arg,
				   struct sk_buff *resp)
{
	struct pn533_cmd_jump_dep_response *rsp;
	struct nfc_target nfc_target;
	u8 target_gt_len;
	int rc;

	if (IS_ERR(resp))
		return PTR_ERR(resp);

	rsp = (struct pn533_cmd_jump_dep_response *)resp->data;

	rc = rsp->status & PN533_CMD_RET_MASK;
	if (rc != PN533_CMD_RET_SUCCESS) {

		queue_work(dev->wq, &dev->rf_work);

		dev_kfree_skb(resp);
		return 0;
	}

	dev_dbg(&dev->interface->dev, "Creating new target");

	nfc_target.supported_protocols = NFC_PROTO_NFC_DEP_MASK;
	nfc_target.nfcid1_len = 10;
	memcpy(nfc_target.nfcid1, rsp->nfcid3t, nfc_target.nfcid1_len);
	rc = nfc_targets_found(dev->nfc_dev, &nfc_target, 1);
	if (rc)
		goto error;

	dev->tgt_available_prots = 0;
	dev->tgt_active_prot = NFC_PROTO_NFC_DEP;


	target_gt_len = resp->len - 17;
	rc = nfc_set_remote_general_bytes(dev->nfc_dev,
					  rsp->gt, target_gt_len);
	if (!rc) {
		rc = nfc_dep_link_is_up(dev->nfc_dev,
					dev->nfc_dev->targets[0].idx,
					0, NFC_RF_INITIATOR);

		if (!rc)
			pn533_poll_reset_mod_list(dev);
	}
error:
	dev_kfree_skb(resp);
	return rc;
}
