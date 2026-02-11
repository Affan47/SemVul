FcParseBlank (FcConfigParse *parse)
{
    int		n = FcVStackElements (parse);
    FcChar32	i, begin, end;
    FcRange	r;

    while (n-- > 0)
    {
	FcVStack    *v = FcVStackFetch (parse, n);
	if (!parse->config->blanks)
	{
	    parse->config->blanks = FcBlanksCreate ();
	    if (!parse->config->blanks)
		goto bail;
	}
	switch ((int) v->tag) {
	case FcVStackInteger:
	    if (!FcBlanksAdd (parse->config->blanks, v->u.integer))
		goto bail;
	    break;
	case FcVStackRange:
	    r = FcRangeCanonicalize (v->u.range);
	    begin = (FcChar32)r.u.d.begin;
	    end = (FcChar32)r.u.d.end;
	    if (begin <= end)
	    {
	      for (i = begin; i <= end; i++)
	      {
		  if (!FcBlanksAdd (parse->config->blanks, i))
		      goto bail;
	      }
	    }
	    break;
	default:
	    FcConfigMessage (parse, FcSevereError, "invalid element in blank");
	    break;
	}
    }
    return;
  bail:
    FcConfigMessage (parse, FcSevereError, "out of memory");
}
