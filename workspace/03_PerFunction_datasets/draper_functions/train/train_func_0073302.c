brcmf_proto_attach(struct brcmf_pub *drvr)
{
	struct brcmf_proto *proto;

	brcmf_dbg(TRACE, "Enter\n");

	proto = kzalloc(sizeof(*proto), GFP_ATOMIC);
	if (!proto)
		goto fail;

	drvr->proto = proto;

	if (drvr->bus_if->proto_type == BRCMF_PROTO_BCDC) {
		if (brcmf_proto_bcdc_attach(drvr))
			goto fail;
	} else if (drvr->bus_if->proto_type == BRCMF_PROTO_MSGBUF) {
		if (brcmf_proto_msgbuf_attach(drvr))
			goto fail;
	} else {
		brcmf_err("Unsupported proto type %d\n",
			  drvr->bus_if->proto_type);
		goto fail;
	}
	if ((proto->txdata == NULL) || (proto->hdrpull == NULL) ||
	    (proto->query_dcmd == NULL) || (proto->set_dcmd == NULL) ||
	    (proto->configure_addr_mode == NULL) ||
	    (proto->delete_peer == NULL) || (proto->add_tdls_peer == NULL)) {
		brcmf_err("Not all proto handlers have been installed\n");
		goto fail;
	}
	return 0;

fail:
	kfree(proto);
	drvr->proto = NULL;
	return -ENOMEM;
}
