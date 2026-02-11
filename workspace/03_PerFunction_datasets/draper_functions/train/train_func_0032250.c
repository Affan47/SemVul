main(int argc, char *argv[])
{
  const char *err;
  const char *image;
  const char *format=FORMAT;
  const char *devopts=NULL;
  int c,usage=0;
  struct cpmSuperBlock sb;
  struct cpmInode root;
  enum Result ret;

  while ((c=getopt(argc,argv,"T:f:nh?"))!=EOF) switch(c)
  {
    case 'f': format=optarg; break;
    case 'T': devopts=optarg; break;
    case 'n': norepair=1; break;
    case 'h':
    case '?': usage=1; break;
  }

  if (optind!=(argc-1)) usage=1;
  else image=argv[optind++];

  if (usage)
  {
    fprintf(stderr,"Usage: %s [-f format] [-n] image\n",cmd);
    exit(1);
  }
  if ((err=Device_open(&sb.dev, image, (norepair ? O_RDONLY : O_RDWR), devopts)))
  {
    if ((err=Device_open(&sb.dev, image,O_RDONLY, devopts)))
    {
      fprintf(stderr,"%s: can not open %s: %s\n",cmd,image,err);
      exit(1);
    }
    else
    {
      fprintf(stderr,"%s: can not open %s for writing, no repair possible\n",cmd,image);
    }
  }
  cpmReadSuper(&sb,&root,format);
  ret=fsck(&root,image);
  if (ret&MODIFIED)
  {
    if (cpmSync(&sb)==-1)
    {
      fprintf(stderr,"%s: write error on %s: %s\n",cmd,image,strerror(errno));
      ret|=BROKEN;
    }
    fprintf(stderr,"%s: FILE SYSTEM ON %s MODIFIED",cmd,image);
    if (ret&BROKEN) fprintf(stderr,", PLEASE CHECK AGAIN");
    fprintf(stderr,"\n");
  }
  cpmUmount(&sb);
  if (ret&BROKEN) return 2;
  else return 0;
}
