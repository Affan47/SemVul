prev_line_id(LINE_ID *line_id, int n)
{
	int r;
	if (line_id->id2 != uid) return 0;
	ID i1 = line_id->id1;
	if (i1 < (uint32)n) {
		r = i1;
		i1 = 0;
	} else {
		r = n;
		i1 -= n;
	}
	if (r) line_id->id1 = i1;
	return r;
}
