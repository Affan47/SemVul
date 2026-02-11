distinguishedname_validate(
	const char *begin,
	const char *end
)
{
	int rc = 0;
	const char *p = begin;
	const char *last = NULL;


	while (p <= end) {
		if ((rc = rdn_validate(p, end, &last)) != 0) {
			goto exit;
		}
		p = last + 1;


		if ((p <= end) && ((p == end) || (*p != ','))) {
			rc = 1;
			goto exit;
		}


		p++;
	}

exit:
	return rc;
}
