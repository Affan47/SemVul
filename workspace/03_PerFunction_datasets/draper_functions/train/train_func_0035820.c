sector_validate_votes(sector_t *sc, vbank_t *rejects)
{
	vbentry_t *itr, *end;

	if (sc->reject_func == NULL) {
		return;
	}

	itr = sc->bank.el;
	end = itr + sc->bank.elems;

	while (itr < end) {
		if (itr->count) {
			validate_vote_entry(sc, itr, rejects);
		}
		itr++;
	}
}
