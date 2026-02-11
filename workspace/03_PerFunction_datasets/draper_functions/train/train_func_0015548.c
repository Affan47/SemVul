blorb_get_story_format(void *blorb_file, int32 extent)
{
 uint32 i, j;

 for(j=0;treaty_registry[j];j++)
 {
  static char fn[512];
  treaty_registry[j](GET_FORMAT_NAME_SEL,NULL,0,fn,512);
  if (blorb_get_chunk(blorb_file,extent,blorb_chunk_for_name(fn),&i, &i)) return fn;
 }
 return NULL;
}
