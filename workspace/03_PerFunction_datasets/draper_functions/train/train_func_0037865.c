check_name(struct find_rock *rock,
		      const char *base, int len)
{
    if (rock->prev) {


	if (len <= rock->prevlen && !memcmp(base, rock->prev, len+1))
	    return 0;
	free(rock->prev);
    }

    rock->prev = xstrndup(base, len);
    rock->prevlen = len;

    return 1;
}
