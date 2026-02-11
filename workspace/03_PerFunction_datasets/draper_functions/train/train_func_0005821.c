jcNext(buf, small, prev)
jcConvBuf *buf;
int small;
int prev;
{
	int	n;

	TRACE("jcNext", "Enter")

	CHECKFIXED(buf);

	if (!buf->clauseInfo[buf->curClause].conv) {

		jcErrno = JE_NOTCONVERTED;
		return -1;
	}


	if (getCandidates(buf, small) < 0)
		return -1;

	n = jl_zenkouho_suu(buf->wnn);
	if (n <= 1) {

		jcErrno = n < 0 ? JE_WNNERROR : JE_NOCANDIDATE;
		return -1;
	}


	n = jl_c_zenkouho(buf->wnn) + (prev ? -1 : 1);
	if (n < 0) {
		n = jl_zenkouho_suu(buf->wnn) - 1;
	} else if (n >= jl_zenkouho_suu(buf->wnn)) {
		n = 0;
	}

	if (setCandidate(buf, n) < 0) {

		jcErrno = JE_WNNERROR;
		return -1;
	}

	return 0;
}
