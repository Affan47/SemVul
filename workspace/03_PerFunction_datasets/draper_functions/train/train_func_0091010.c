zGetIntergenicContinueScore(zTrellis* trellis) {
	int iso_group = trellis->tiso_group;

	if (iso_group < 0 || iso_group >= trellis->hmm->iso_transitions ) {
		zDie("zGetIntergenicContinueScore: iso_group %d not found\n",
			 iso_group);
	}
	return trellis->hmm->inter_continue[iso_group];
}
