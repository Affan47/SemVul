T1_GetFileSearchPath( int type)
{
  static char *out_ptr;
  int i;
  int pathlen;
  char **src_ptr=NULL;


  if (out_ptr!=NULL)
    free( out_ptr);
  out_ptr=NULL;

  if (type & T1_PFAB_PATH) {
    src_ptr=T1_PFAB_ptr;
  }
  else  if (type & T1_AFM_PATH) {
    src_ptr=T1_AFM_ptr;
  }
  else if (type & T1_ENC_PATH) {
    src_ptr=T1_ENC_ptr;
  }
  else if (type & T1_FDB_PATH) {
    src_ptr=T1_FDB_ptr;
  }


  i=0;
  pathlen=0;
  while (src_ptr[i]!=NULL) {
    pathlen +=strlen( src_ptr[i++]);
    pathlen+=1;
  }
  if ((out_ptr=(char *)malloc(pathlen+1))==NULL) {
    T1_errno=T1ERR_ALLOC_MEM;
    return( NULL);
  }
  strcpy( out_ptr, src_ptr[0]);
  i=1;
  while (src_ptr[i]!=NULL) {
    strcat( out_ptr, path_sep_string);
    strcat( out_ptr, src_ptr[i++]);
  }

  return( out_ptr);

}
