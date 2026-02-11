dsgw_emitr (int depth, const char* s, size_t n)
{
    static const char* linebreak = "' +\n'";
    static const size_t linebreak_len = 5;
    auto size_t result = 0;
    if (n == 0) {
	return 0;
    } else if (depth == 0) {
	return dsgw_fputn (stdout, s, n);
    }
    --depth;
    switch (quotation_type[depth]) {
      case QUOTATION_JAVASCRIPT:
      case QUOTATION_JAVASCRIPT_MULTILINE:
      case QUOTATION_JAVASCRIPT_ENDOFLINE:
	{
	    auto const char* t;
	    for (t = s; (t = strnbrk (t, n, "'\\\n")) != NULL; ++t) {
		switch (*t) {
		  case '\n':
		    if (t != s) {
			if (quotation_type[depth] == QUOTATION_JAVASCRIPT_ENDOFLINE) {
			    dsgw_emitr (depth, linebreak, linebreak_len);
			}
			result += dsgw_emitr (depth, s, t - s);
		    }
		    if (dsgw_emitr (depth, "\\n", 2) > 1) ++result;
		    if (quotation_type[depth] == QUOTATION_JAVASCRIPT_MULTILINE) {
			quotation_type[depth] = QUOTATION_JAVASCRIPT_ENDOFLINE;
		    }
		    break;
		  default:
		    if (quotation_type[depth] == QUOTATION_JAVASCRIPT_ENDOFLINE) {
			quotation_type[depth] = QUOTATION_JAVASCRIPT_MULTILINE;
			dsgw_emitr (depth, linebreak, linebreak_len);
		    }
		    result += dsgw_emitr (depth, s, t - s);
		    dsgw_emitr (depth, "\\", 1);
		    result += dsgw_emitr (depth, t, 1);
		    break;
		}
		n -= (t - s) + 1;
		s = t + 1;
	    }
	}
	if (n > 0 &&
	    quotation_type[depth] == QUOTATION_JAVASCRIPT_ENDOFLINE) {
	    quotation_type[depth] = QUOTATION_JAVASCRIPT_MULTILINE;
	    dsgw_emitr (depth, linebreak, linebreak_len);
	}
	break;
      default:
	break;
    }
    if (n > 0) {
	result += dsgw_emitr (depth, s, n);
    }
    return result;
}
