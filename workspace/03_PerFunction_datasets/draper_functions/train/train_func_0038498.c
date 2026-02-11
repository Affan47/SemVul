path_clean(char* p)
{
	char* d = p;
	char* anchors[2] = {d,d};
	char prev = 0;
	int sta = 1;
	while (*p) {
		if (*p == '/') {

			if (prev == '/') d--;

			if (sta == 2) d = anchors[0];

			if (sta == 3) d = anchors[1];
			anchors[1] = anchors[0];
			anchors[0] = d;
			sta = 1;
		} else {
			if (sta && *p == '.') {
				sta++;
			} else {
				sta = 0;
			}
		}
		prev = *p;
		*d = *p;
		d++;
		p++;
	}
	*d = 0;
}
