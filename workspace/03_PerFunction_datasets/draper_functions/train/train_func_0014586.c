innobase_convert_identifier(

	char*		buf,
	ulint		buflen,
	const char*	id,
	ulint		idlen,
	void*		thd,
	ibool		file_id)

{
	char nz[NAME_LEN + 1];
	char nz2[NAME_LEN + 1 + EXPLAIN_FILENAME_MAX_EXTRA_LENGTH];

	const char*	s	= id;
	int		q;

	if (file_id) {


		if (UNIV_UNLIKELY(idlen > (sizeof nz) - 1)) {
			idlen = (sizeof nz) - 1;
		}

		memcpy(nz, id, idlen);
		nz[idlen] = 0;

		s = nz2;
		idlen = explain_filename((THD*) thd, nz, nz2, sizeof nz2,
					 EXPLAIN_PARTITIONS_AS_COMMENT);
		goto no_quote;
	}


	if (UNIV_UNLIKELY(!thd)) {
		q = '"';
	} else {
		q = get_quote_char_for_identifier((THD*) thd, s, (int) idlen);
	}

	if (q == EOF) {
no_quote:
		if (UNIV_UNLIKELY(idlen > buflen)) {
			idlen = buflen;
		}
		memcpy(buf, s, idlen);
		return(buf + idlen);
	}


	if (buflen < 2) {
		return(buf);
	}

	*buf++ = q;
	buflen--;

	for (; idlen; idlen--) {
		int	c = *s++;
		if (UNIV_UNLIKELY(c == q)) {
			if (UNIV_UNLIKELY(buflen < 3)) {
				break;
			}

			*buf++ = c;
			*buf++ = c;
			buflen -= 2;
		} else {
			if (UNIV_UNLIKELY(buflen < 2)) {
				break;
			}

			*buf++ = c;
			buflen--;
		}
	}

	*buf++ = q;
	return(buf);
}
