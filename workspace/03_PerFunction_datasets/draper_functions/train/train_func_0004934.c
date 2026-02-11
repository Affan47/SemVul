realloc(uint32 alloc_length)
{
  uint32 len=ALIGN_SIZE(alloc_length+1);
  DBUG_ASSERT(len > alloc_length);
  if (len <= alloc_length)
    return TRUE;
  if (Alloced_length < len)
  {
    char *new_ptr;
    if (alloced)
    {
      if (!(new_ptr= (char*) my_realloc(Ptr,len,MYF(MY_WME))))
        return TRUE;
    }
    else if ((new_ptr= (char*) my_malloc(len,MYF(MY_WME))))
    {
      if (str_length > len - 1)
        str_length= 0;
      if (str_length)
	memcpy(new_ptr,Ptr,str_length);
      new_ptr[str_length]=0;
      alloced=1;
    }
    else
      return TRUE;
    Ptr= new_ptr;
    Alloced_length= len;
  }
  Ptr[alloc_length]=0;
  return FALSE;
}
