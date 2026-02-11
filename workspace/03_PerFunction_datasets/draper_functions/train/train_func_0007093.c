xsh_get_binning(cpl_frameset* raws,int* binx, int* biny)
{
  cpl_frame* frame=NULL;
  const char* name=NULL;
  cpl_propertylist* plist=NULL;
  int nraw=0;

  XSH_ASSURE_NOT_NULL_MSG(raws,"Null pointer for input raw frameset");
  nraw=cpl_frameset_get_size(raws);

  XSH_ASSURE_NOT_ILLEGAL_MSG(nraw > 0,"nraw = 0 Provide at least a raw frame");

  check(frame=cpl_frameset_get_first(raws));
  check(name=cpl_frame_get_filename(frame));
  check(plist=cpl_propertylist_load(name,0));
  check(*binx=xsh_pfits_get_binx(plist));
  check(*biny=xsh_pfits_get_biny(plist));

 cleanup:
  xsh_free_propertylist(&plist);

  return;
}
