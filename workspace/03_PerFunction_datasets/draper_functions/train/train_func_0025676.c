jcSelect(buf, n)
jcConvBuf *buf;
int n;
{
	TRACE("jcSelect", "Enter")

	CHECKFIXED(buf);

#ifdef DEBUG_WNNLIB
	fprintf(stderr,
		"Select: %d [%s for %d - %d]\n",
		n,
		buf->candKind == CAND_SMALL ? "small" : "large",
		buf->candClause,
		buf->candClauseEnd);
#endif


	if (buf->candClause < 0) {
		jcErrno = JE_NOCANDIDATE;
		return -1;
	}


	if (n < 0 || n >= jl_zenkouho_suu(buf->wnn)) {
		jcErrno = JE_NOSUCHCANDIDATE;
		return -1;
	}


	if (jl_c_zenkouho(buf->wnn) != n && setCandidate(buf, n) < 0)
		return -1;

	return 0;
}
