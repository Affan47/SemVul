used_blob_length(CACHE_FIELD **ptr)
{
  uint length,blob_length;
  for (length=0 ; *ptr ; ptr++)
  {
    Field_blob *field_blob= (Field_blob *) (*ptr)->field;
    (*ptr)->blob_length=blob_length= field_blob->get_length();
    length+=blob_length;
    field_blob->get_ptr(&(*ptr)->str);
  }
  return length;
}
