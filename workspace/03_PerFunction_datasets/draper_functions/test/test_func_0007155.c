JustifiedPutStringFont(SDL_Surface * Surface, BFont_Info * Font, int y, char *text)
{
	int spaces = 0;
	int gap;
	int single_gap;
	int dif;

	char *strtmp;
	char *p;
	int pos = -1;
	int xpos = 0;

	if (strchr(text, ' ') == NULL) {
		PutStringFont(Surface, Font, 0, y, text);
	} else {
		gap = (Surface->w - 1) - TextWidthFont(Font, text);

		if (gap <= 0) {
			PutStringFont(Surface, Font, 0, y, text);
		} else {
			spaces = count(text);
			dif = gap % spaces;
			single_gap = (gap - dif) / spaces;
			xpos = 0;
			pos = -1;
			while (spaces > 0) {
				p = strstr(&text[pos + 1], " ");
				strtmp = NULL;
				strtmp = (char *)calloc((p - &text[pos + 1]) + 1, sizeof(char));
				if (strtmp != NULL) {
					strncpy(strtmp, &text[pos + 1], (p - &text[pos + 1]));
					PutStringFont(Surface, Font, xpos, y, strtmp);
					xpos = xpos + TextWidthFont(Font, strtmp) + single_gap + CharWidth(Font, ' ');
					if (dif >= 0) {
						xpos++;
						dif--;
					}
					pos = p - text;
					spaces--;
					free(strtmp);
				}
			}
			strtmp = NULL;
			strtmp = (char *)calloc(strlen(&text[pos + 1]) + 1, sizeof(char));

			if (strtmp != NULL) {
				strncpy(strtmp, &text[pos + 1], strlen(&text[pos + 1]));
				PutStringFont(Surface, Font, xpos, y, strtmp);
				free(strtmp);
			}
		}
	}
}
