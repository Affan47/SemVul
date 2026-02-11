mmap_string_realloc_memory(MMAPString * string)
{
  char * tmp;

  tmp =  realloc (string->str, string->allocated_len);

  if (tmp == NULL)
    string = NULL;
  else
    string->str = tmp;

  return string;
}
