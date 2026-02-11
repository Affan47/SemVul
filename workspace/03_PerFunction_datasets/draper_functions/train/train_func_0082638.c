makeConverted(buf, cl)
jcConvBuf *buf;
int cl;
{
	int	nsbun;
	int	next;
	int	status;
	wchar	savechar;
	jcClause	*clpc, *clpn;

	TRACE("makeConverted", "Enter")

#ifdef DEBUG_WNNLIB
	showBuffers(buf, "before makeConverted");
#endif


	nsbun = jl_bun_suu(buf->wnn);
	if (cl <= nsbun)
		return 0;


	clpc = buf->clauseInfo + nsbun;
	for (; nsbun < cl; nsbun = next, clpc = clpn) {
		clpn = clpc + 1;
		next = nsbun + 1;


		if (clpc->conv == 1)
			continue;


		savechar = *clpn->dispp;
		*clpn->dispp = 0;


		status = jl_tan_conv(buf->wnn, clpc->dispp,
					nsbun, next, WNN_NO_USE, WNN_SHO);


		*clpn->dispp = savechar;

		if (status < 0) {
			jcErrno = JE_WNNERROR;
			return -1;
		}
	}

#ifdef DEBUG_WNNLIB
	showBuffers(buf, "after makeConverted");
#endif

	return 0;
}
