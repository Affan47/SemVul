insert1(int flag, int l, uint8_t *s, bprope6_t *bpr, bcr_t *bcr)
{
	int i;
	if ((flag & FLAG_ODD) && (l&1) == 0) {
		for (i = 0; i < l>>1; ++i)
			if (s[i] + s[l-1-i] != 5) break;
		if (i == l>>1) --l;
	}
	if (flag & FLAG_FOR) {
		if (bpr) bpr_insert_string(bpr, l, s);
		if (bcr) bcr_append(bcr, l, s);
	}
	if (flag & FLAG_REV) {
		for (i = 0; i < l>>1; ++i) {
			int tmp = s[l-1-i];
			tmp = (tmp >= 1 && tmp <= 4)? 5 - tmp : tmp;
			s[l-1-i] = (s[i] >= 1 && s[i] <= 4)? 5 - s[i] : s[i];
			s[i] = tmp;
		}
		if (l&1) s[i] = (s[i] >= 1 && s[i] <= 4)? 5 - s[i] : s[i];
		if (bpr) bpr_insert_string(bpr, l, s);
		if (bcr) bcr_append(bcr, l, s);
	}
}
