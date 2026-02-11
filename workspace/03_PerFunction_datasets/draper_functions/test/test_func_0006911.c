ncbytesfree(NCbytes* bb)
{
  if(bb == NULL) return;
  if(!bb->nonextendible && bb->content != NULL) free(bb->content);
  free(bb);
}
