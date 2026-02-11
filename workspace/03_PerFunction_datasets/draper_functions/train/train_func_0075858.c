mkfmindexoptions(Mkfmcallinfo *mkfmcallinfo,
                            int argc,const char **argv,GtError *err)
{
  GtOPrval rval;
  int retval = 0;

  gt_error_check(err);
  rval = parsemkfmindex(mkfmcallinfo,argc,argv,err);
  if (rval == GT_OPTION_PARSER_ERROR)
  {
    retval = -1;
  } else
  {
    if (rval == GT_OPTION_PARSER_REQUESTS_EXIT)
    {
      retval = 2;
    }
  }
  return retval;
}
