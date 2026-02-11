lookup_comp(int comp, int mode, int relation,
			  void **comprock)
{
    comparator_t *ret;

    ret = NULL;
    *comprock = NULL;
#if VERBOSE
    printf("comp%d mode%d relat%d     \n", comp, mode, relation);
#endif
    switch (comp)
      {
      case B_OCTET:
 	switch (mode) {
	  case B_IS:
	    ret = &rel_eq;
	    *comprock = (void **) &octet_cmp;
	    break;
	  case B_CONTAINS:
	    ret = &octet_contains;
	    break;
	  case B_MATCHES:
	    ret = &octet_matches;
	    break;
#ifdef ENABLE_REGEX
	  case B_REGEX:
	    ret = &octet_regex;
	    break;
#endif
	  case B_VALUE:
	    ret = lookup_rel(relation);
	    *comprock = (void **) &octet_cmp;
	    break;
	}
	break;
      case B_ASCIICASEMAP:
     	switch (mode) {
	case B_IS:
	    ret = &rel_eq;
	    *comprock = (void **) &ascii_casemap_cmp;
	    break;
	case B_CONTAINS:
	    ret = &ascii_casemap_contains;
	    break;
	case B_MATCHES:
	    ret = &ascii_casemap_matches;
	    break;
#ifdef ENABLE_REGEX
	case B_REGEX:


	    ret = &octet_regex;
	    break;
#endif
	case B_VALUE:
	    ret = lookup_rel(relation);
	    *comprock = (void **) &ascii_casemap_cmp;
	    break;
	}
	break;
      case B_ASCIINUMERIC:
	switch (mode) {
	case B_IS:
	    ret = &rel_eq;
	    *comprock = (void **) &ascii_numeric_cmp;
	    break;
	case B_COUNT:
	case B_VALUE:
	    ret = lookup_rel(relation);
	    *comprock = (void **) &ascii_numeric_cmp;
	    break;
	}
	break;
      }
    return ret;
}
