fgetline(char **line, size_t *linesize, size_t *count, size_t *llen,
		FILE *fp, int appendnl)
{
	long i_llen, sz;

	if (count == NULL)


		return fgetline_byone(line, linesize, llen, fp, appendnl, 0);
	if (*line == NULL || *linesize < LINESIZE)
		*line = srealloc(*line, *linesize = LINESIZE);
	sz = *linesize <= *count ? *linesize : *count + 1;
	if (sz <= 1 || fgets(*line, sz, fp) == NULL)


		return NULL;
	i_llen = length_of_line(*line, sz);
	*count -= i_llen;
	while ((*line)[i_llen - 1] != '\n') {
		*line = srealloc(*line, *linesize += 256);
		sz = *linesize - i_llen;
		sz = (sz <= *count ? sz : *count + 1);
		if (sz <= 1 || fgets(&(*line)[i_llen], sz, fp) == NULL) {
			if (appendnl) {
				(*line)[i_llen++] = '\n';
				(*line)[i_llen] = '\0';
			}
			break;
		}
		sz = length_of_line(&(*line)[i_llen], sz);
		i_llen += sz;
		*count -= sz;
	}
	if (llen)
		*llen = i_llen;
	return *line;
}
