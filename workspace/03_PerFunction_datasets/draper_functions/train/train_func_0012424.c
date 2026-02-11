GetDefDiskObject(LONG def_type)
{
  static char *defnames[]= {
    "disk", "drawer", "tool", "project",
    "garbage", "device", "kick", "appicon"
  };
  static char *icondir=NULL;
  static int l;
  char *buf;
  struct DiskObject *diskobj;

  if(def_type<WBDISK || def_type>WBAPPICON)
    return NULL;
  if(!icondir)
    if(!(icondir = get_current_icondir()))
      return NULL;
    else
      l = strlen(icondir);

#ifdef HAVE_ALLOCA
  buf = alloca(l+18);
#else
  buf = malloc(l+18);
  if(buf==NULL) return NULL;
#endif
  sprintf(buf, "%s/def_%s.info", icondir, defnames[def_type-WBDISK]);
  diskobj=int_load_do(buf);
#ifndef HAVE_ALLOCA
  free(buf);
#endif
  return diskobj;
}
