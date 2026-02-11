copyhist(hist, keep)
CONST char *hist;
int keep;
{
#ifdef	DEP_ORIGSHELL
	int y1, y2, len2;

	len2 = vlen(inputbuf, inputlen);
	y1 = ptr2line(len2);
	if (dumbmode) {
		setcursor(0, 0);
		clearline();
	}
#endif

	if (!keep) {
		inputlen = (hist) ? strlen(hist) : 0;
		insertbuf(0);
		if (hist) memcpy(inputbuf, hist, inputlen + 1);
		else *inputbuf = '\0';
		if (rptr < 0 || rptr > inputlen) {
			rptr = inputlen;
			vptr = vlen(inputbuf, rptr);
		}
	}
	displaystr();

#ifdef	DEP_ORIGSHELL
	if (dumbmode) ;
	else if (shellmode) {
		y2 = ptr2line(vlen(inputbuf, inputlen));
		if (y1 > y2) {
			while (y1 > y2) {
				locate2(0, y1--);
				Xputterm(L_CLEAR);
			}
			setcursor(rptr, vptr);
		}
	}
#endif
}
