get_token_arg(char *src, char **skip_to)
{
    int   quotes = 0, done = 0;
    char *ret = NULL, *p;

    while(*src && isspace((unsigned char)*src))
      src++;

    if(*src == RPAREN){
	if(skip_to)
	  *skip_to = src;

	return(ret);
    }

    p = ret = (char *)fs_get((strlen(src) + 1) * sizeof(char));
    while(!done){
	switch(*src){
	  case QUOTE:
	    if(++quotes == 2)
	      done++;

	    src++;
	    break;

	  case BSLASH:
	    if(*(src+1) == BSLASH || *(src+1) == QUOTE){
		src++;
		*p++ = *src++;
	    }
	    else
	      src++;

	    break;

	  case SPACE:
	  case TAB:
	  case RPAREN:
	  case COMMA:
	    if(quotes)
	      *p++ = *src++;
	    else
	      done++;

	    break;

	  case '\0':
	    done++;
	    break;

	  default:
	    *p++ = *src++;
	    break;
	}
    }

    *p = '\0';
    if(skip_to)
      *skip_to = src;

    return(ret);
}
