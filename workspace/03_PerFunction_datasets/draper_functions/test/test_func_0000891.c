zDNAScoreWMM (zScanner *scanner, coor_t pos) {
	coor_t i;
	score_t score;
	coor_t mfocus = pos - scanner->model->focus;
	int num;


	if ((pos < scanner->min_pos) || (pos > scanner->max_pos))
		return MIN_SCORE;


	score = 0;
	for (i = 0; i < scanner->model->length; i++) {
		num = (i * scanner->model->symbols) + zGetDNAS5(scanner->seq->parent,i + mfocus);

		score += scanner->model->data[num];
	}
	return score;
}
