GFile_get_modified(GFile *file,GTimeVal *act, gboolean update_mark){
  GFileInfo *info;
  GError *error=NULL;
  if (!file) return FALSE;
  info=g_file_query_info (file,"time::modified,time::modified-usec",0,NULL,&error);
  if (error){
  g_error_free(error);
  return FALSE;
  }
  GTimeVal result;
  g_file_info_get_modification_time (info,&result);
  gboolean hr=FALSE;
  if ((result.tv_sec > act->tv_sec) || (result.tv_sec == act->tv_sec && result.tv_usec > act->tv_usec)) hr=TRUE;
  if (update_mark){

    act->tv_sec=result.tv_sec;
    act->tv_usec =result.tv_usec;
  }
  g_object_unref(info);
  return hr;
}
