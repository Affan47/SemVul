ParseObject(AString *token, int ships)
{
	int r = -1;
	for (int i=O_DUMMY+1; i<NOBJECTS; i++) {
		if (*token == ObjectDefs[i].name) {
			if(ObjectDefs[i].flags & ObjectType::DISABLED) return -1;
			r = i;
			break;
		}
	}

	if((r == -1) && (ships > 0)) {
		for (int i=0; i<NITEMS; i++) {
			if(ItemDefs[i].type & IT_SHIP) {
				if ((*token == ItemDefs[i].name) ||
					(*token == ItemDefs[i].abr)) {
						if(ItemDefs[i].flags & ItemType::DISABLED) return -1;
						r = -(i+1);
						break;
				}
			}
		}
	}

	return r;
}
