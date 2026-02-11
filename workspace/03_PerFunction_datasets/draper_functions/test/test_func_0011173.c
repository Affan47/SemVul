uea_dispatch_cmv_e1(struct uea_softc *sc, struct intr_pkt *intr)
{
	struct cmv_dsc_e1 *dsc = &sc->cmv_dsc.e1;
	struct cmv_e1 *cmv = &intr->u.e1.s2.cmv;

	uea_enters(INS_TO_USBDEV(sc));
	if (le16_to_cpu(cmv->wPreamble) != E1_PREAMBLE)
		goto bad1;

	if (cmv->bDirection != E1_MODEMTOHOST)
		goto bad1;


	if (cmv->bFunction != dsc->function) {
		if (UEA_CHIP_VERSION(sc) == ADI930
				&& cmv->bFunction ==  E1_MAKEFUNCTION(2, 2)) {
			cmv->wIndex = cpu_to_le16(dsc->idx);
			put_unaligned_le32(dsc->address,
						&cmv->dwSymbolicAddress);
			cmv->wOffsetAddress = cpu_to_le16(dsc->offset);
		} else
			goto bad2;
	}

	if (cmv->bFunction == E1_MAKEFUNCTION(E1_ADSLDIRECTIVE,
							E1_MODEMREADY)) {
		wake_up_cmv_ack(sc);
		uea_leaves(INS_TO_USBDEV(sc));
		return;
	}


	if (le16_to_cpu(cmv->wIndex) != dsc->idx ||
	    get_unaligned_le32(&cmv->dwSymbolicAddress) != dsc->address ||
	    le16_to_cpu(cmv->wOffsetAddress) != dsc->offset)
		goto bad2;

	sc->data = get_unaligned_le32(&cmv->dwData);
	sc->data = sc->data << 16 | sc->data >> 16;

	wake_up_cmv_ack(sc);
	uea_leaves(INS_TO_USBDEV(sc));
	return;

bad2:
	uea_err(INS_TO_USBDEV(sc), "unexpected cmv received, "
			"Function : %d, Subfunction : %d\n",
			E1_FUNCTION_TYPE(cmv->bFunction),
			E1_FUNCTION_SUBTYPE(cmv->bFunction));
	uea_leaves(INS_TO_USBDEV(sc));
	return;

bad1:
	uea_err(INS_TO_USBDEV(sc), "invalid cmv received, "
			"wPreamble %d, bDirection %d\n",
			le16_to_cpu(cmv->wPreamble), cmv->bDirection);
	uea_leaves(INS_TO_USBDEV(sc));
}
