ParseGiveableItem(AString *token)
{
	int r = -1;
	for (int i=0; i<NITEMS; i++) {
		if(ItemDefs[i].flags & ItemType::DISABLED) continue;
		if(ItemDefs[i].flags & ItemType::CANTGIVE) continue;
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
