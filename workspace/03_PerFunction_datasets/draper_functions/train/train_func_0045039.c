xsh_set_recipe_file_prefix(cpl_frameset* raw,const char* recipe)
{

  cpl_frame* frm=NULL;
  cpl_propertylist* plist=NULL;
  const char* obj=NULL;
  char* prefix=NULL;

  const char* dpr_catg=NULL;

  const char* dpr_type=NULL;
  const char* filename=NULL;

  check(frm=cpl_frameset_get_frame(raw,0));
  filename=cpl_frame_get_filename(frm);
  plist=cpl_propertylist_load(filename,0);
  dpr_catg=xsh_pfits_get_dpr_catg(plist);

  dpr_type=xsh_pfits_get_dpr_type(plist);

  if(strstr(dpr_catg,"SCIENCE")!=NULL) {
     if(strstr(dpr_type,"SKY")!=NULL) {
        obj="SKY";
     } else {
        obj="SCI";
     }
  } else if(strstr(dpr_catg,"CALIB")!=NULL) {
    if(strstr(dpr_type,"FLUX")!=NULL) {
      obj="FLUX";
    } else if(strstr(dpr_type,"TELLURIC")!=NULL) {
      obj="TELL";
    } else {
      obj="CAL";
    }
  } else {
      obj="OBJ";
  }

  if(strstr(recipe,"respon_slit_stare")!=NULL) {
    prefix=xsh_stringcat_any(obj,"_SLIT",NULL);
  } else if(strstr(recipe,"respon_slit_offset")!=NULL) {
    prefix=xsh_stringcat_any(obj,"_SLIT",NULL);
  } else if(strstr(recipe,"respon_slit_nod")!=NULL) {
    prefix=xsh_stringcat_any(obj,"_SLIT",NULL);
  } else if(strstr(recipe,"scired_slit_stare")!=NULL) {
    prefix=xsh_stringcat_any(obj,"_SLIT",NULL);
  } else if(strstr(recipe,"scired_slit_offset")!=NULL) {
    prefix=xsh_stringcat_any(obj,"_SLIT",NULL);
  } else if(strstr(recipe,"scired_slit_nod")!=NULL) {
    prefix=xsh_stringcat_any(obj,"_SLIT",NULL);
  } else if(strstr(recipe,"scired_ifu_stare")!=NULL) {
    prefix=xsh_stringcat_any(obj,"_IFU",NULL);
  } else if(strstr(recipe,"scired_ifu_offset")!=NULL) {
    prefix=xsh_stringcat_any(obj,"_IFU",NULL);
  } else if(strstr(recipe,"geom_ifu")!=NULL) {
    prefix=xsh_stringcat_any(obj,"_IFU",NULL);
  } else {
    xsh_msg_warning("recipe %s not supported",recipe);
    prefix=xsh_stringcat_any(obj,"",NULL);
  }


 cleanup:
  xsh_free_propertylist(&plist);

  return prefix;
}
