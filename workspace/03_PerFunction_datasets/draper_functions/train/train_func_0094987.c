clear_pending_isac_ints(struct IsdnCardState *cs)
{
	int val, eval;

	val = cs->readisac(cs, ISAC_STAR);
	debugl1(cs, "ISAC STAR %x", val);
	val = cs->readisac(cs, ISAC_MODE);
	debugl1(cs, "ISAC MODE %x", val);
	val = cs->readisac(cs, ISAC_ADF2);
	debugl1(cs, "ISAC ADF2 %x", val);
	val = cs->readisac(cs, ISAC_ISTA);
	debugl1(cs, "ISAC ISTA %x", val);
	if (val & 0x01) {
		eval = cs->readisac(cs, ISAC_EXIR);
		debugl1(cs, "ISAC EXIR %x", eval);
	}
	val = cs->readisac(cs, ISAC_CIR0);
	debugl1(cs, "ISAC CIR0 %x", val);
	cs->dc.isac.ph_state = (val >> 2) & 0xf;
	schedule_event(cs, D_L1STATECHANGE);

	cs->writeisac(cs, ISAC_MASK, 0xFF);
}
