p_get_elem_size(GapPlayerCacheElem *elem_ptr)
{
  gint32 bytesize;

  bytesize = 0;

  if(elem_ptr)
  {
    if(elem_ptr->cdata)
    {
      bytesize = elem_ptr->cdata->th_data_size;
    }
    if(elem_ptr->ckey)
    {
      bytesize += strlen(elem_ptr->ckey);
    }
    bytesize += (sizeof(GapPlayerCacheElem) + sizeof(GapPlayerCacheData));
  }

  return(bytesize);

}
