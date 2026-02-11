catenate(struct Global *global, ReturnCode *ret)
{


#if OK_CONCAT
  int c;
  char *token1;
#endif

#if OK_CONCAT
  if (get(global) != TOK_SEP) {
    unget(global);
    return (FALSE);
  }
  else {
    token1 = savestring(global, global->tokenbuf);
    c=get(global);
    if(global->rightconcat) {
      *ret=macroid(global, &c);
      if(*ret)
	return(FALSE);
    } else
      lookid(global, c);
    switch(type[c]) {
    case LET:
      if ((int)strlen(token1) + (int)strlen(global->tokenbuf) >= NWORK) {
	cfatal(global, FATAL_WORK_AREA_OVERFLOW, token1);
	*ret=FPP_WORK_AREA_OVERFLOW;
	return(FALSE);
      }
      sprintf(global->work, "%s%s", token1, global->tokenbuf);
      break;
    case DIG:
    case DOT:
      strcpy(global->work, token1);
      global->workp = global->work + strlen(global->work);
      *ret=scannumber(global, c, save);
      if(*ret)
	return(FALSE);
      *ret=save(global, EOS);
      if(*ret)
	return(FALSE);
      break;
    default:
      if (isprint(c))
	cerror(global, ERROR_STRANG_CHARACTER, c);
      else
	cerror(global, ERROR_STRANG_CHARACTER2, c);
      strcpy(global->work, token1);
      unget(global);
      break;
    }


    Freemem(token1);
    *ret=ungetstring(global, global->work);
    if(*ret)
      return(FALSE);
    return(TRUE);
  }
#else
  return(FALSE);
#endif
}
