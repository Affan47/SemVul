unlimitroman(ptr, llenp, minp, maxp)
int ptr, *llenp, *minp, *maxp;
{
	int i, n, c, min, max;

	min = -1;
	max = maxromanlist;
	if (ptr) {
		if (--ptr) {
			min = *minp;
			max = *maxp;
			i = ptr - 1;
			if ((n = min + 1) >= max || i >= romanlist[n].len)
				return(-1);
			c = romanlist[n].str[i];
			for (; min >= 0; min--) {
				if (i >= romanlist[min].len) break;
				if (c != romanlist[min].str[i]) break;
			}
			for (; max < maxromanlist; max++) {
				if (i >= romanlist[max].len) break;
				if (c != romanlist[max].str[i]) break;
			}
		}
	}
	else if (isvalidbuf(kjisbuf)) {
		kjisbuf.max = 0;
		VOID_C romanprompt(0, llenp);
	}
	else if (isvalidbuf(rjisbuf)) {
		(rjisbuf.max)--;
		*llenp = countjisbuf(&rjisbuf);
	}
	else ptr = -2;

	*minp = min;
	*maxp = max;

	return(ptr);
}
