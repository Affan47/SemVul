isac_setup(struct isac *isac)
{
	int val, eval;

	isac->type = TYPE_ISAC;
	isac_version(isac);

	ph_command(isac, ISAC_CMD_RES);

	isac->write_isac(isac, ISAC_MASK, 0xff);
	isac->mocr = 0xaa;
	if (test_bit(ISAC_IOM1, &isac->flags)) {

		isac->write_isac(isac, ISAC_ADF2, 0x0);
		isac->write_isac(isac, ISAC_SPCR, 0xa);
		isac->write_isac(isac, ISAC_ADF1, 0x2);
		isac->write_isac(isac, ISAC_STCR, 0x70);
		isac->write_isac(isac, ISAC_MODE, 0xc9);
	} else {

		if (!isac->adf2)
			isac->adf2 = 0x80;
		isac->write_isac(isac, ISAC_ADF2, isac->adf2);
		isac->write_isac(isac, ISAC_SQXR, 0x2f);
		isac->write_isac(isac, ISAC_SPCR, 0x00);
		isac->write_isac(isac, ISAC_STCR, 0x70);
		isac->write_isac(isac, ISAC_MODE, 0xc9);
		isac->write_isac(isac, ISAC_TIMR, 0x00);
		isac->write_isac(isac, ISAC_ADF1, 0x00);
	}
	val = isac->read_isac(isac, ISAC_STAR);
	DBG(2, "ISAC STAR %x", val);
	val = isac->read_isac(isac, ISAC_MODE);
	DBG(2, "ISAC MODE %x", val);
	val = isac->read_isac(isac, ISAC_ADF2);
	DBG(2, "ISAC ADF2 %x", val);
	val = isac->read_isac(isac, ISAC_ISTA);
	DBG(2, "ISAC ISTA %x", val);
	if (val & 0x01) {
		eval = isac->read_isac(isac, ISAC_EXIR);
		DBG(2, "ISAC EXIR %x", eval);
	}
	val = isac->read_isac(isac, ISAC_CIR0);
	DBG(2, "ISAC CIR0 %x", val);
	FsmEvent(&isac->l1m, (val >> 2) & 0xf, NULL);

	isac->write_isac(isac, ISAC_MASK, 0x0);

	isac->write_isac(isac, ISAC_CMDR, ISAC_CMDR_XRES | ISAC_CMDR_RRES);
}
