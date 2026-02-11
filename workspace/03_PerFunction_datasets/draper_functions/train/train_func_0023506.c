fwrite_td(void *ptr, size_t size, size_t nmemb, FILE *f, enum tdflags flags,
		char *prefix, size_t prefixlen)
{
	char *upper;
	size_t sz, csize;
#ifdef	HAVE_ICONV
	char *iptr, *nptr;
	size_t inleft, outleft;
#endif
	char *mptr, *xmptr, *mlptr = NULL;
	size_t mptrsz;

	csize = size * nmemb;
	mptrsz = csize;
	mptr = xmptr = ac_alloc(mptrsz + 1);
#ifdef	HAVE_ICONV
	if ((flags & TD_ICONV) && iconvd != (iconv_t)-1) {
	again:	inleft = csize;
		outleft = mptrsz;
		nptr = mptr;
		iptr = ptr;
		if (iconv_ft(iconvd, &iptr, &inleft, &nptr, &outleft) ==
					(size_t)-1 &&
				errno == E2BIG) {
			iconv(iconvd, NULL, NULL, NULL, NULL);
			ac_free(mptr);
			mptrsz += inleft;
			mptr = ac_alloc(mptrsz + 1);
			goto again;
		}
		nmemb = mptrsz - outleft;
		size = sizeof (char);
		ptr = mptr;
		csize = size * nmemb;
	} else
#endif
	{
		memcpy(mptr, ptr, csize);
	}
	upper = mptr + csize;
	*upper = '\0';
	if (flags & TD_ISPR) {
		struct str	in, out;
		in.s = mptr;
		in.l = csize;
		makeprint(&in, &out);
		mptr = mlptr = out.s;
		csize = out.l;
	}
	if (flags & TD_DELCTRL)
		csize = delctrl(mptr, csize);
	sz = prefixwrite(mptr, sizeof *mptr, csize, f, prefix, prefixlen);
	ac_free(xmptr);
	free(mlptr);
	return sz;
}
