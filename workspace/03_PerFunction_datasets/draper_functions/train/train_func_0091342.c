lightpen_select(int baddr)
{
	int faddr;
	register unsigned char	fa;
	int designator;
#if defined(X3270_DBCS)
	int designator2;
#endif

	faddr = find_field_attribute(baddr);
	fa = ea_buf[faddr].fa;
	if (!FA_IS_SELECTABLE(fa)) {
		ring_bell();
		return;
	}
	designator = faddr;
	INC_BA(designator);

#if defined(X3270_DBCS)
	if (dbcs) {
		if (ea_buf[baddr].cs == CS_DBCS) {
			designator2 = designator;
			INC_BA(designator2);
			if ((ea_buf[designator].db != DBCS_LEFT &&
			     ea_buf[designator].db != DBCS_LEFT_WRAP) &&
			    (ea_buf[designator2].db != DBCS_RIGHT &&
			     ea_buf[designator2].db != DBCS_RIGHT_WRAP)) {
				ring_bell();
				return;
			}
			if (ea_buf[designator].cc == 0x42 &&
			    ea_buf[designator2].cc == EBC_greater) {
				ctlr_add(designator2, EBC_question, CS_DBCS);
				mdt_clear(faddr);
			} else if (ea_buf[designator].cc == 0x42 &&
				   ea_buf[designator2].cc == EBC_question) {
				ctlr_add(designator2, EBC_greater, CS_DBCS);
				mdt_clear(faddr);
			} else if ((ea_buf[designator].cc == EBC_space &&
				    ea_buf[designator2].cc == EBC_space) ||
			           (ea_buf[designator].cc == EBC_null &&
				    ea_buf[designator2].cc == EBC_null)) {
				ctlr_add(designator2, EBC_greater, CS_DBCS);
				mdt_set(faddr);
				key_AID(AID_SELECT);
			} else if (ea_buf[designator].cc == 0x42 &&
				   ea_buf[designator2].cc == EBC_ampersand) {
				mdt_set(faddr);
				key_AID(AID_ENTER);
			} else {
				ring_bell();
			}
			return;
		}
	}
#endif

	switch (ea_buf[designator].cc) {
	    case EBC_greater:
		ctlr_add(designator, EBC_question, 0);
		mdt_clear(faddr);
		break;
	    case EBC_question:
		ctlr_add(designator, EBC_greater, 0);
		mdt_set(faddr);
		break;
	    case EBC_space:
	    case EBC_null:
		mdt_set(faddr);
		key_AID(AID_SELECT);
		break;
	    case EBC_ampersand:
		mdt_set(faddr);
		key_AID(AID_ENTER);
		break;
	    default:
		ring_bell();
		break;
	}
}
