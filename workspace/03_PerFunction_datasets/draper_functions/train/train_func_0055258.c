resetDecay() {
	for (Scores::size_type i = 1, end = score.size(); i < end; ++i) {
		decayedScore(i);
		score[i].dec = 0;
	}
	decay = 0;
}
