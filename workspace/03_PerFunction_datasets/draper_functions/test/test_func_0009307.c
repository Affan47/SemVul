_showtree(list, max, nest, y)
treelist *list;
int max, nest, y;
{
	char *cp;
	int i, j, w, tmp;

	w = TREEFIELD - (nest * DIRFIELD) - 1;
	tmp = y;
	for (i = 0; i < max; i++) {
		if (nest > 0) {
			for (j = tmp; j < y; j++) {
				if (j <= 0 || j >= FILEPERROW) continue;
				cp = bufptr(j);
				cp[(nest - 1) * DIRFIELD] = '|';
			}
		}
		if (y > 0 && y < FILEPERROW) {
			cp = bufptr(y);
			if (nest > 0)
				memcpy(&(cp[(nest - 1) * DIRFIELD]), "+--", 3);
			if (!(list[i].name)) {
				tmp = (w > 3) ? 3 : w;
				memcpy(&(cp[nest * DIRFIELD]), "...", tmp);
			}
			else {
				tmp = Xsnprintf(&(cp[nest * DIRFIELD]),
					w * KANAWID + 1,
					"%^.*s", w, list[i].name);
#ifdef	CODEEUC
				tmp = strlen(&(cp[nest * DIRFIELD]));
#endif
				cp[nest * DIRFIELD + tmp] =
					(list[i].max < 0) ? '>' : ' ';
			}
		}
		y++;
		tmp = y;
		if (w >= DIRFIELD && list[i].sub)
			y = _showtree(list[i].sub, list[i].max, nest + 1, y);
	}

	return(y);
}
