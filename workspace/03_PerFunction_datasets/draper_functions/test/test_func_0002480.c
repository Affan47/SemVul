isac_exi_interrupt(struct isac *isac)
{
	unsigned char val;

	val = isac->read_isac(isac, ISAC_EXIR);
	DBG(2, "EXIR %#x", val);

	if (val & ISAC_EXIR_XMR) {
		DBG(DBG_WARN, "ISAC XMR");
		isac_retransmit(isac);
	}
	if (val & ISAC_EXIR_XDU) {
		DBG(DBG_WARN, "ISAC XDU");
		isac_retransmit(isac);
	}
	if (val & ISAC_EXIR_MOS) {
		DBG(DBG_WARN, "MOS");
		val = isac->read_isac(isac, ISAC_MOSR);
		DBG(2, "ISAC MOSR %#x", val);
	}
}
