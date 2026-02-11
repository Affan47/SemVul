_new_StringMemString(StringMem *sm, size_t length)
{
  char *string;
  int was_malloc;


  if(!sm)
    return NULL;
  if(length < 1)
    length = 1;


  if(length < SM_STRLEN) {
    string = (char *)_new_FreeListNode(sm->fl);
    if(!string)
      return NULL;
    was_malloc = 0;
  } else {
    string = (char *) malloc(length+1);
    if(!string)
      return NULL;


    was_malloc = 1;
    sm->nmalloc++;
  };


  string[0] = (char) was_malloc;
  return string + 1;
}
