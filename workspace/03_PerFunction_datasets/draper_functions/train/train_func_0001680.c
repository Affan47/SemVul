isDepthAxis(const char *stdname, const char *longname)
{
  int status = FALSE;

  if ( strcmp(stdname, "depth") == 0 ) status = TRUE;

  if ( status == FALSE )
    if ( strcmp(longname, "depth_below_sea") == 0 ||
         strcmp(longname, "depth below sea") == 0 )
      {
        status = TRUE;
      }

  return (status);
}
