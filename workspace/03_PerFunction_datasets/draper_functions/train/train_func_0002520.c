ast_remaining_ms(struct timeval start, int max_ms)
{
	int ms;

	if (max_ms < 0) {
		ms = max_ms;
	} else {
		ms = max_ms - ast_tvdiff_ms(ast_tvnow(), start);
		if (ms < 0) {
			ms = 0;
		}
	}

	return ms;
}
