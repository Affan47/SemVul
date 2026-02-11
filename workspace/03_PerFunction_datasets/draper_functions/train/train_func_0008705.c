parse_intvl(char *str)
{
    char *q;
    long  left, right;
    INTVL_S *ret = NULL, **next;

    if(!str)
      return(ret);

    q = str;

    for(;;){
	left = right = INTVL_UNDEF;


	while(isspace((unsigned char) *q) || *q == LPAREN)
	  q++;


	if(*q == COMMA || !struncmp(q, "-INF", 4))
	  left = - INTVL_INF;
	else if(*q == '-' || isdigit((unsigned char) *q))
	  left = atol(q);

	if(left != INTVL_UNDEF){

	    while(*q && *q != COMMA && *q != RPAREN)
	      q++;
	    if(*q == COMMA)
	      q++;
	    while(isspace((unsigned char) *q))
	      q++;


	    if(*q == '\0' || *q == RPAREN || !struncmp(q, "INF", 3))
	      right = INTVL_INF;
	    else if(*q == '-' || isdigit((unsigned char) *q))
	      right = atol(q);
	}

	if(left == INTVL_UNDEF || right == INTVL_UNDEF
	   || left > right){
	    if(left != INTVL_UNDEF || right != INTVL_UNDEF || *q){
		if(left != INTVL_UNDEF && right != INTVL_UNDEF
		   && left > right)
		  q_status_message1(SM_ORDER, 3, 5,
				_("Error: Interval \"%s\", min > max"), str);
		else
		  q_status_message1(SM_ORDER, 3, 5,
		      _("Error: Interval \"%s\": syntax is (min,max)"), str);

		if(ret)
		  free_intvl(&ret);

		ret = NULL;
	    }

	    break;
	}
	else{
	    if(!ret){
		ret = (INTVL_S *) fs_get(sizeof(*ret));
		memset((void *) ret, 0, sizeof(*ret));
		ret->imin = left;
		ret->imax = right;
		next = &ret->next;
	    }
	    else{
		*next = (INTVL_S *) fs_get(sizeof(*ret));
		memset((void *) *next, 0, sizeof(*ret));
		(*next)->imin = left;
		(*next)->imax = right;
		next = &(*next)->next;
	    }


	    while(*q && *q != COMMA && *q != RPAREN)
	      q++;
	    if(*q == RPAREN)
	      q++;
	    while(*q && *q != COMMA)
	      q++;
	    if(*q == COMMA)
	      q++;
	}
    }

    return(ret);
}
