combine(ht_undo_data *ud)
{
	if (ud->getObjectID()==getObjectID()) {
		ht_undo_data_overwrite_string *ud2 = (ht_undo_data_overwrite_string *)ud;
		if (ud2->cpos.line == cpos.line) {
			if (ud2->apos.pofs == apos.pofs + len) {
				string = realloc(string, len + ud2->len);
				memcpy((byte*)string+len, ud2->string, ud2->len);
				len += ud2->len;
				bpos = ud2->bpos;
				if (ud2->len2) {
					if (!len2) {
						string2 = malloc(ud2->len2);
						memcpy(string2, ud2->string2, ud2->len2);
					} else {
						string2 = realloc(string2, len2 + ud2->len2);
						memcpy((byte*)string2+len2, ud2->string2, ud2->len2);
					}
					len2 += ud2->len;
				}
				return true;
			}
		}
	}
	return false;
}
