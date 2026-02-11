Make_RegularExpression_Type(va_list *ap)
{
#if HAVE_REGEX_H_FUNCS
  char *rx = va_arg(*ap, char *);
  RegExp_Arg *preg;

  preg = typeMalloc(RegExp_Arg, 1);

  if (preg)
    {
      T((T_CREATE("RegExp_Arg %p"), preg));
      if (((preg->pRegExp = typeMalloc(regex_t, 1)) != 0)
	  && !regcomp(preg->pRegExp, rx,
		      (REG_EXTENDED | REG_NOSUB | REG_NEWLINE)))
	{
	  T((T_CREATE("regex_t %p"), preg->pRegExp));
	  preg->refCount = typeMalloc(unsigned long, 1);

	  *(preg->refCount) = 1;
	}
      else
	{
	  if (preg->pRegExp)
	    free(preg->pRegExp);
	  free(preg);
	  preg = (RegExp_Arg *)0;
	}
    }
  return ((void *)preg);
#elif HAVE_REGEXP_H_FUNCS | HAVE_REGEXPR_H_FUNCS
  char *rx = va_arg(*ap, char *);
  RegExp_Arg *pArg;

  pArg = typeMalloc(RegExp_Arg, 1);

  if (pArg)
    {
      int blen = RX_INCREMENT;

      T((T_CREATE("RegExp_Arg %p"), pArg));
      pArg->compiled_expression = NULL;
      pArg->refCount = typeMalloc(unsigned long, 1);

      *(pArg->refCount) = 1;

      do
	{
	  char *buf = typeMalloc(char, blen);

	  if (buf)
	    {
#if HAVE_REGEXP_H_FUNCS
	      char *last_pos = compile(rx, buf, &buf[blen], '\0');

#else
	      char *last_pos = compile(rx, buf, &buf[blen]);
#endif
	      if (reg_errno)
		{
		  free(buf);
		  if (reg_errno == 50)
		    blen += RX_INCREMENT;
		  else
		    {
		      free(pArg);
		      pArg = NULL;
		      break;
		    }
		}
	      else
		{
		  pArg->compiled_expression = buf;
		  break;
		}
	    }
	}
      while (blen <= MAX_RX_LEN);
    }
  if (pArg && !pArg->compiled_expression)
    {
      free(pArg);
      pArg = NULL;
    }
  return (void *)pArg;
#else
  return 0;
#endif
}
