psread(int fh, void *buf, int cnt, bool valid_eof = false)
{
	int res = read(fh, buf, cnt);

	if (res == cnt)
		return;
	if (res == 0 && valid_eof)
		fprintf(stderr, "end of file\n");
	else
		fprintf(stderr, "broken stream\n");
	statistics();
	exit(1);
}
