deep_babel_ifiction(char stopped)
{
  char buffer[TREATY_MINIMUM_EXTENT];
  char *md;
  char *ep;
  int32 i;
  FILE *f;

  if (stopped!=2)
  {
  i=babel_treaty(GET_STORY_FILE_IFID_SEL,buffer,TREATY_MINIMUM_EXTENT);
  if (i==0 && !babel_md5_ifid(buffer, TREATY_MINIMUM_EXTENT))
  {
   fprintf(stderr,"Unable to create an IFID (A serious problem occurred while loading the file).\n");
   return;
  }


  ep=strtok(buffer, ",");
  }
  else ep="-";
  i=babel_treaty(GET_STORY_FILE_METADATA_EXTENT_SEL,NULL,0);
  if (i<=0)
  {
   if (stopped) printf("No iFiction record for %s\n",buffer);
   return;
  }
  md=(char *)my_malloc(i,"Metadata buffer");
  if (babel_treaty(GET_STORY_FILE_METADATA_SEL,md,i)<0)
  {
    fprintf(stderr,"A serious error occurred while retrieving metadata.\n");
    free(md);
    return;
  }
  while(ep)
  {
   char epb[TREATY_MINIMUM_EXTENT+9];
   if (stopped!=2)
   {
   strcpy(epb,ep);
   strcat(epb, IFICTION_EXT);

   f=fopen(epb,"w");
   }
   else f=stdout;

   if (!f || fputs(md,f)==EOF)
    fprintf(stderr,"A serious error occurred writing to disk.\n");
   else if (stopped!=2) printf("Extracted %s\n",epb);
   if (f) fclose(f);
   if (stopped) break;
   ep=strtok(NULL,",");
  }
  free(md);
}
