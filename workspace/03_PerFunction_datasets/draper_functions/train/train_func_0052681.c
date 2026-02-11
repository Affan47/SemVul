GetValueR(FILE *fp, char *str, void *v, int c)
{
 char buf[256];
 int s;

 while(FReadString(fp,buf,256))
 {
  fread(&s,1,4,fp);
  if(!strcmp(str, buf))
  {
   if(!c)
   {
    if(!(*(char **)v=(char*)malloc(s)))
     goto gogl;
    fread(*(char **)v,1,s,fp);
    continue;
   }
   else if(s>c || s<c)
   {
     gogl:
     fseek(fp,s,SEEK_CUR);
     continue;
   }
   fread((uint8*)v,1,c,fp);
  }
  else
   fseek(fp,s,SEEK_CUR);
 }
 fseek(fp,4,SEEK_SET);
}
