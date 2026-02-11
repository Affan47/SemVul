es_strCaseContains(es_str_t *s1, es_str_t *s2)
{
	es_size_t i, j;
	es_size_t max;
	unsigned char *c1, *c2;
	int r;

	r = -1;
	if(s2->lenStr > s1->lenStr) {

		goto done;
	}

	c1 = es_getBufAddr(s1);
	c2 = es_getBufAddr(s2);
	max = s1->lenStr - s2->lenStr + 1;
	for(i = 0 ; i < max ; ++i) {
		for(j = 0 ; j < s2->lenStr; ++j) {
			if(tolower(c1[i+j]) != tolower(c2[j]))
				break;
		}
		if(j == s2->lenStr) {
			r = i;
			break;
		}
	}

done:	return r;
}
