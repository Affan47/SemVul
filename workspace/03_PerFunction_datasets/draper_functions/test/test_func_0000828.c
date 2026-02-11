replace_quotes(long int linenum, char *line, LT_INS_S **ins, void *local)
{
    char *lp = line, *prefix = NULL, *last_prefix = NULL;
    int no_more_quotes = 0, len, saw_quote = 0;

    if(ps_global->VAR_QUOTE_REPLACE_STRING){
	get_pair(ps_global->VAR_QUOTE_REPLACE_STRING, &prefix, &last_prefix, 0, 0);
	if(!prefix && last_prefix){
	    prefix = last_prefix;
	    last_prefix = NULL;
	}
    }
    else
      return(0);

    while(isspace((unsigned char)(*lp)))
      lp++;
    while(*lp && !no_more_quotes){
	switch(*lp++){
	  case '>':
	    if(*lp == ' '){
		ins = gf_line_test_new_ins(ins, lp - 1, "", -2);
		lp++;
	    }
	    else
	      ins = gf_line_test_new_ins(ins, lp - 1, "", -1);
	    if(strlen(prefix))
	      ins = gf_line_test_new_ins(ins, lp, prefix, strlen(prefix));
	    saw_quote = 1;
	    break;
	  case TAG_EMBED:
	    switch(*lp++){
	      case TAG_FGCOLOR:
	      case TAG_BGCOLOR:
		len = RGBLEN;
		break;
	      case TAG_HANDLE:
		len = *lp++ + 1;
		break;
	    }
	    if(strlen(lp) < len)
	      no_more_quotes = 1;
	    else
	      lp += len;
	    break;
	  case ' ':
	  case '\t':
	    break;
	  default:
	    if(saw_quote && last_prefix)
	      ins = gf_line_test_new_ins(ins, lp - 1, last_prefix, strlen(last_prefix));
	    no_more_quotes = 1;
	    break;
	}
    }
    if(prefix)
      fs_give((void **)&prefix);
    if(last_prefix)
      fs_give((void **)&last_prefix);
    return(0);
}
