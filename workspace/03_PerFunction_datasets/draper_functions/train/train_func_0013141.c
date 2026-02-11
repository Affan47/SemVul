es_addBuf(es_str_t **ps1, char *buf, es_size_t lenBuf)
{
	int r;
	es_size_t newlen;
	es_str_t *s1 = *ps1;

	ASSERT_STR(s1);
	if(lenBuf == 0) {
		r = 0;
		goto done;
	}

	newlen = s1->lenStr + lenBuf;
	if(s1->lenBuf < newlen) {

		if((r = es_extendBuf(ps1, newlen - s1->lenBuf)) != 0) goto done;
		s1 = *ps1;
	}


	memcpy(es_getBufAddr(s1)+s1->lenStr, buf, lenBuf);
	s1->lenStr = newlen;
	r = 0;

done:
	return r;
}
