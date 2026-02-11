zInternalTransBack(zTrellis *trellis, int from_state,
						int to_state, coor_t i) {
    zScanner* scanner;
	zStrIdx   feature;
	score_t   total_score;
	int       ps;

	feature = trellis->hmm->state[from_state].model;
	ps = ('-' != trellis->hmm->state[from_state].strand);

	scanner = (ps) ? trellis->scanner[feature] :
					 trellis->rscanner[feature];

	total_score = scanner->score(scanner, (ps) ? i : trellis->dna->length-i-1)
	  + zGetTransitionScore(trellis->hmm, from_state, to_state,trellis->tiso_group)
	  + trellis->backward[to_state][i+1];

	trellis->backward[from_state][i] =
	  zFloatwiseScoreAdd(total_score, trellis->backward[from_state][i]);
}
