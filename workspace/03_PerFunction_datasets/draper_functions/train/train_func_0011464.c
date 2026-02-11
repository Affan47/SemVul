sinfo_update_fits_card_long(const char* file,const char* card,long value)
{
  cpl_propertylist *   plist =NULL;
  if ((plist = cpl_propertylist_load(file, 0)) == NULL) {
    sinfo_msg_error( "getting header from file %s",file);
    cpl_propertylist_delete(plist) ;
    return -1 ;
  }
  if (CPL_ERROR_NONE!=cpl_propertylist_set_long(plist,card,value)){
    sinfo_msg_error( "setting header of file %s",file);
    cpl_propertylist_delete(plist) ;
    return -1 ;
  }
  cpl_propertylist_delete(plist) ;
  return 0;
}
