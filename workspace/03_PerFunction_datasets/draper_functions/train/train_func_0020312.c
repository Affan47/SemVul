record_hit (Unit *unit, Key *k, uae_u32 pos, uae_u32 len, uae_u32 mode)
{
	bool exclusive = mode == REC_EXCLUSIVE || mode == REC_EXCLUSIVE_IMMED;
	for (Key *k2 = unit->keys; k2; k2 = k2->next) {
		if (k2->aino->uniq == k->aino->uniq) {
			if (k2 == k)
				continue;
			for (struct lockrecord *lr = k2->record; lr; lr = lr->next) {
				bool exclusive2 = lr->mode == REC_EXCLUSIVE || lr->mode == REC_EXCLUSIVE_IMMED;
				if (exclusive || exclusive2) {
					uae_u32 a1 = pos;
					uae_u32 a2 = pos + len;
					uae_u32 b1 = lr->pos;
					uae_u32 b2 = lr->pos + lr->len;
					if (len && lr->len) {
						bool hit = (a1 >= b1 && a1 < b2) || (a2 > b1 && a2 < b2) || (b1 >= a1 && b1 < a2) || (b2 > a1 && b2 < a2);
						if (hit)
							return true;
					}
				}
			}
		}
	}
	return false;
}
