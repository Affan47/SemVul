claim_story_file(void *story_file, int32 extent)
{
 unsigned char *sf=(unsigned char *)story_file;
 uint32 i,j;
 if (extent<0x3c ||
     sf[0] < 1 ||
     sf[0] > 8
    ) return INVALID_STORY_FILE_RV;
 for(i=4;i<=14;i+=2)
 {
  j=read_zint(sf+i);
  if (j>(uint32) extent || j < 0x40) return INVALID_STORY_FILE_RV;
 }

 return VALID_STORY_FILE_RV;
}
