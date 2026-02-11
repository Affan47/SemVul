ebcdic_to_multibyte_x(ebc_t ebc, unsigned char cs, char mb[],
	int mb_len, unsigned flags, ucs4_t *ucp)
{
	ucs4_t uc;

#if defined(_WIN32)
	int nc;
	BOOL udc;
	wchar_t wuc;
#elif defined(UNICODE_WCHAR)
	int nc;
	wchar_t wuc;
#else
	char u8b[7];
	size_t nu8;
	ici_t inbuf;
	char *outbuf;
	size_t inbytesleft, outbytesleft;
	size_t nc;
#endif


	uc = ebcdic_to_unicode(ebc, cs, flags);
	if (ucp != NULL)
		*ucp = uc;
	if (uc == 0) {
		if (flags & EUO_BLANK_UNDEF) {
			mb[0] = ' ';
			mb[1] = '\0';
			return 2;
		} else {
			return 0;
		}
	}


#if defined(_WIN32)


	wuc = uc;
	nc = WideCharToMultiByte(LOCAL_CODEPAGE, 0, &wuc, 1, mb, mb_len,
		"?", &udc);
	if (nc != 0) {
		mb[nc++] = '\0';
		return nc;
	} else {
		mb[0] = '?';
		mb[1] = '\0';
		return 2;
	}

#elif defined(UNICODE_WCHAR)


	if (is_utf8) {
		nc = unicode_to_utf8(uc, mb);
		if (nc < 0)
			return 0;
		mb[nc++] = '\0';
		return nc;
	}

	wuc = uc;
	nc = wctomb(mb, uc);
	if (nc > 0) {

		nc += wctomb(mb + nc, 0);
		return nc;
	} else {
		mb[0] = '?';
		mb[1] = '\0';
		return 2;
	}
#else


	nu8 = unicode_to_utf8(uc, u8b);
	if (nu8 < 0)
		return 0;


	if (is_utf8) {
	    memcpy(mb, u8b, nu8);
	    mb[nu8++] = '\0';
	    return nu8;
	}


	inbuf = u8b;
	inbytesleft = nu8;
	outbuf = mb;
	outbytesleft = mb_len;
	nc = iconv(i_u2mb, &inbuf, &inbytesleft, &outbuf, &outbytesleft);
	if (nc < 0 || inbytesleft == nu8) {
		mb[0] = '?';
		mb[1] = '\0';
		return 2;
	}


	nc = iconv(i_u2mb, NULL, NULL, &outbuf, &outbytesleft);
	if (nc < 0) {
		mb[0] = '?';
		mb[1] = '\0';
		return 0;
	}


	mb[mb_len - outbytesleft--] = '\0';
	return mb_len - outbytesleft;

#endif
}
