LodePNG_UnknownChunks_cleanup(LodePNG_UnknownChunks* chunks)
{
  unsigned i;
  for(i = 0; i < 3; i++) free(chunks->data[i]);
}
