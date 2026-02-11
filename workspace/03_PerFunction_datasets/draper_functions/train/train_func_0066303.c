ocbytesfill(OCbytes* bb, char fill)
{
  unsigned int i;
  if(bb == NULL) return ocbytesfail();
  for(i=0;i<bb->length;i++) bb->content[i] = fill;
  return TRUE;
}
