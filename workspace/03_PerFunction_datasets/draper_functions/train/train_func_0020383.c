get_model(u16 manf_id, u16 card_id)
{

	if (manf_id == CF8305_MANFID && card_id == CF8305_CARDID)
		return MODEL_8305;
	else if (manf_id == CF8381_MANFID && card_id == CF8381_CARDID)
		return MODEL_8381;
	else if (manf_id == CF8385_MANFID && card_id == CF8385_CARDID)
		return MODEL_8385;
	return MODEL_UNKNOWN;
}
