type2_command(int cmd, const uint8_t *data, int *left)
{
    switch (cmd) {

      case Cs::cCallsubr:
      case Cs::cCallgsubr:
	if (subr_depth() < MAX_SUBR_DEPTH && size() == 1) {

	    bool g = (cmd == Cs::cCallgsubr);
	    CsRef csref = ((int)top() + program()->xsubr_bias(g)) | (g ? CSR_GSUBR : CSR_SUBR);
	    Subr *callee = csr_subr(csref, true);
	    if (callee)
		_cur_subr->add_call(callee);

	    int left = csgen().length();

	    bool more = callxsubr_command(g);

	    int right = csgen().length();
	    if (error() >= 0 && callee)
		callee->add_caller(_cur_subr, left, right - left);
	    return more;
	} else {

	    goto normal;
	}

      normal:
      default:
	return CharstringInterp::type2_command(cmd, data, left);

    }
}
