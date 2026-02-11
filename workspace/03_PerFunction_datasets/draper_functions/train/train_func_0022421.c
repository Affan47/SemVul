tlog3b_xgcb_wptgr(const char* args, const char** unused)
{
  if (xmlgrid != NULL) {
    if (strcmp(xmlgrid, args) == 0) {
      return;
    }
    xfree(xmlgrid);
  }
  xmlgrid = xstrdup(args);
}
