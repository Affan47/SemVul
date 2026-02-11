skip_over_name_with_stop(p, stop)
char *p ;
char *stop ;
{
    char in_quote = 0 ;
    int ignore_parens ;
    int parenth_level = 0 ;

    ignore_parens = strchr(stop, ')') || strchr(stop, '(') ;

    while (*p) {
	switch (*p) {
	  case '\"':
	  case '\'':
	  case '`':
	    if (in_quote) {
		if (in_quote == *p) {
		    in_quote = 0 ;
		}
	    } else {
		in_quote = *p ;
	    }
	    break ;
	  case '(':


	    if (!ignore_parens) {
		parenth_level++ ;
		break ;
	    }
	  case ')':
	    if (!ignore_parens) {
		if (parenth_level <= 0) {
		    parsing_error("unmatched closing parenthesis", p, NULL) ;
		}
		parenth_level-- ;
		break ;
	    }
	  default:
	    if (!in_quote &&
		(is_no_namecomponent(*p) || strchr(stop, *p)) &&
		(ignore_parens || parenth_level == 0)) {


		return p ;
	    }
	}
	p++ ;
    }


    if (in_quote) {
	parsing_error("non-terminated quoting at end of line", p - 1, NULL) ;
    }


    if (!ignore_parens && parenth_level != 0) {
	parsing_error("mismatched parenthesis", p, NULL) ;
    }

    return p ;
}
