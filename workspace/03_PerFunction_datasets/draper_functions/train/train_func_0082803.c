get_line_vlength(uint line)
{
	char l[1024];
	char *linep=l;
	uint vl=0;

	uint linelen;
	if (!textfile->getline(line, 0, l, sizeof l, &linelen, NULL)) return 0;

	while (linelen--) vl+=char_vsize(*(linep++), vl);

	return vl;
}
