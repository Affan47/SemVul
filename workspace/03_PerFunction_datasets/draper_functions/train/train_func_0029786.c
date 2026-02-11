pf_read_hexstring(pfstate *pf) {
    rdstringc rsc = { 0, 0, NULL };
    int c;

    rdaddc(&rsc, '<');
    do {
	c = pf_getc(pf);
	if (c != EOF) rdaddc(&rsc, c);
    } while (c != '>' && c != EOF);
    return rsc.text;
}
