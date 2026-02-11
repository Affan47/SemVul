out_grouping_b_U(struct SN_env * z, const unsigned char * s, int min, int max, int repeat) {
    do {
	int ch;
	int w = get_b_utf8(z->p, z->c, z->lb, & ch);
	unless (w) return -1;
	unless (ch > max || (ch -= min) < 0 || (s[ch >> 3] & (0X1 << (ch & 0X7))) == 0)
	    return w;
	z->c -= w;
    } while (repeat);
    return 0;
}
