blorb_get_resource(void *blorb_file, int32 extent, char *rid, int32 nnumber, uint32 *begin, uint32 *output_extent)
{
 uint32 ridx_len;
 uint32 i,j;
 uint32 number=(uint32) nnumber;
 void *ridx;
 if (blorb_get_chunk(blorb_file, extent,"RIdx",&i,&ridx_len)==NO_REPLY_RV)
  return NO_REPLY_RV;

 ridx=(char *)blorb_file+i+4;
 ridx_len=read_int((char *)blorb_file+i);
 for(i=0;i<ridx_len;i++)
 {
  if (memcmp((char *)ridx+(i*12),rid,4)==0 && read_int((char *)ridx+(i*12)+4)==number)
  {
   j=i;
   i=read_int((char *)ridx+(j*12)+8);
   *begin=i+8;
   *output_extent=read_int((char *)blorb_file+i+4);
   return 1;
  }
 }
 return NO_REPLY_RV;
}
