ParseEnabledItem(AString *token)
{
	int r = -1;

	if ((*token=="CLIP") || (*token=="Clipper") || (*token=="Clippers"))
		*token = "KNARR";
	if ((*token=="GLON") || (*token=="Galleon") || (*token=="Galleons"))
		*token = "COG";
	for (int i=0; i<NITEMS; i++) {
		if(ItemDefs[i].flags & ItemType::DISABLED) continue;
		if (ItemDefs[i].type & IT_ILLUSION) {
			if ((*token == (AString("i") + ItemDefs[i].name)) ||
				(*token == (AString("i") + ItemDefs[i].names)) ||
				(*token == (AString("i") + ItemDefs[i].abr))) {
				r = i;
				break;
			}
		} else {
			if ((*token == ItemDefs[i].name) ||
				(*token == ItemDefs[i].names) ||
				(*token == ItemDefs[i].abr)) {
				r = i;
				break;
			}
		}
	}
	if(r != -1) {
		if(ItemDefs[r].flags & ItemType::DISABLED) r = -1;
	}
	return r;
}
