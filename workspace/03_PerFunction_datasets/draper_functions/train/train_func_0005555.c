xsh_pfits_combine_headers(cpl_propertylist* header,cpl_frameset* set)
{
  int size=0;
  int i=0;
  int expno_min=999;
  int expno_max=-999;
  int expno_cur=0;
  int i_min=0;
  int i_max=0;
  cpl_propertylist* plist=NULL;
  cpl_propertylist* head_first=NULL;
  cpl_propertylist* head_last=NULL;
  const char* fname=NULL;
  cpl_frame* frame=NULL;

  cpl_error_ensure(header != NULL, CPL_ERROR_NULL_INPUT,
                  return CPL_ERROR_NULL_INPUT, "NULL input header");
  cpl_error_ensure(set != NULL, CPL_ERROR_NULL_INPUT,
                   return CPL_ERROR_NULL_INPUT, "NULL input frameset");

  size=cpl_frameset_get_size(set);
  if(size == 1) {
      return CPL_ERROR_NONE;
  }
  for(i=0;i<size;i++) {
      frame=cpl_frameset_get_frame(set,i);
      fname=cpl_frame_get_filename(frame);


      plist=cpl_propertylist_load(fname,0);
      expno_cur=xsh_pfits_get_tpl_expno(plist);

      if(expno_cur < expno_min) {
          expno_min=expno_cur;
          i_min=i;
      }
      if(expno_cur > expno_max) {
          expno_max=expno_cur;
          i_max=i;
      }
      xsh_free_propertylist(&plist);
  }

  frame=cpl_frameset_get_frame(set,i_min);
  fname=cpl_frame_get_filename(frame);


  head_first=cpl_propertylist_load_regexp(fname,0,"START",0);
  cpl_propertylist_copy_property_regexp(header,head_first,"START",0);


  frame=cpl_frameset_get_frame(set,i_max);
  fname=cpl_frame_get_filename(frame);


  head_last=cpl_propertylist_load_regexp(fname,0,"END",0);
  cpl_propertylist_copy_property_regexp(header,head_last,"END",0);


  xsh_free_propertylist(&head_first);
  xsh_free_propertylist(&head_last);
  xsh_free_propertylist(&plist);

  return cpl_error_get_code();

}
