get_story_file_IFID(void *s_file, int32 extent, char *output, int32 output_extent)
{

 int32 i,j;
 char ser[9];
 char buffer[32];
 char *story_file = (char *) s_file;


 if (extent<0x0B) return INVALID_STORY_FILE_RV;

 for(i=0;i<extent;i++) if (memcmp((char *)story_file+i,"UUID://",7)==0) break;
 if (i<extent)
  {
   for(j=i+7;j<extent && ((char *)story_file)[j]!='/';j++);
   if (j<extent)
   {
    i+=7;
    ASSERT_OUTPUT_SIZE(j-i);
    memcpy(output,(char *)story_file+i,j-i);
    output[j-i]=0;
    return 1;
   }
  }

 memcpy(ser, (char *) story_file+0x03, 8);
 ser[8]=0;

 for(j=0;j<8;j++)
  if (!isalnum(ser[j])) ser[j]='-';


 sprintf(buffer,"HUGO-%d-%02X-%02X-%s",story_file[0],story_file[1], story_file[2],ser);

 ASSERT_OUTPUT_SIZE((signed) strlen(buffer)+1);
 strcpy((char *)output,buffer);
 return 1;
}
