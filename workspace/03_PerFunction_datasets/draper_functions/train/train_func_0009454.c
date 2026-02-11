prioritize(MOVE *mp0, int n)
{
	int i, j, s, w, pile[NNEED], npile;
	card_t card, need[4];
	MOVE *mp;


	for (i = 0; i < NNEED; ++i) {
		pile[i] = -1;
	}
	npile = 0;

	for (s = 0; s < 4; ++s) {
		need[s] = NONE;
		if (O[s] == NONE) {
			need[s] = Osuit[s] + PS_ACE;
		} else if (O[s] != PS_KING) {
			need[s] = Osuit[s] + O[s] + 1;
		}
	}


	for (w = 0; w < Nwpiles; ++w) {
		j = Wlen[w];
		for (i = 0; i < j; ++i) {
			card = W[w][i];
			s = SUIT(card);


			if (need[s] != NONE &&
			    (card == need[s] || card == need[s] + 1)) {
				pile[npile++] = w;
				if (npile == NNEED) {
					break;
				}
			}
		}
		if (npile == NNEED) {
			break;
		}
	}


	for (i = 0, mp = mp0; i < n; ++i, ++mp) {
		if (mp->card_index != -1) {
			w = mp->from;
			for (j = 0; j < npile; ++j) {
				if (w == pile[j]) {
					mp->pri += Xparam[0];
				}
			}
			if (Wlen[w] > 1) {
				card = W[w][Wlen[w] - 2];
				for (s = 0; s < 4; ++s) {
					if (card == need[s]) {
						mp->pri += Xparam[1];
						break;
					}
				}
			}
			if (mp->totype == W_Type) {
				for (j = 0; j < npile; ++j) {
					if (mp->to == pile[j]) {
						mp->pri -= Xparam[2];
					}
				}
			}
		}
	}
}
