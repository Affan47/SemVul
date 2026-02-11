next_line_id(LINE_ID *line_id, int n)
{
	if (line_id->id3 != uid) return 0;
	int c = 0;
	FileOfs o = (uint64(line_id->id1) << 32) + line_id->id2;
	if (o < disp && disp < fsize) {
		o = disp;
		c++;
		n--;
	}
	while (n--) {
		if (o + line_length >= fsize) break;
		o += line_length;
		c++;
	}
	if (o < disp) {
		o = 0;
	} else {
		o = o - (o-disp)%line_length;
	}
	line_id->id1 = o >> 32;
	line_id->id2 = o;
	return c;
}
