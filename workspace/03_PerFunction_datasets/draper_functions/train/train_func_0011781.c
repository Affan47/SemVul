claim_story_file(void *story_file, int32 exten)
{
 unsigned char *sf=(unsigned char *)story_file;
 int32 i;
 int32 scale;
 uint32 extent=(uint32) exten;

 if (!story_file || extent < 0x28) return  INVALID_STORY_FILE_RV;

 if (sf[0]<34) scale=4;
 else scale=16;
 for(i=3;i<0x0B;i++) if (sf[i]<0x20 || sf[i]>0x7e) return INVALID_STORY_FILE_RV;
 for(i=0x0b;i<0x18;i+=2)
 if (read_hugo_addx(sf+i) * scale > extent) return INVALID_STORY_FILE_RV;

 return VALID_STORY_FILE_RV;
}
