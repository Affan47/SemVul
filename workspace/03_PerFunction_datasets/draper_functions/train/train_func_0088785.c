main(int argc,char** argv)
{
  FILE* in=stdin;
  int j,width,height,paddedWidth;
  char buffer[1024];
  rfbScreenInfoPtr rfbScreen;

  if(argc>1) {
    in=fopen(argv[1],"rb");
    if(!in) {
      printf("Couldn't find file %s.\n",argv[1]);
      exit(1);
    }
  }

  fgets(buffer,1024,in);
  if(strncmp(buffer,"P6",2)) {
    printf("Not a ppm.\n");
    exit(2);
  }


  do {
    fgets(buffer,1024,in);
  } while(buffer[0]=='#');


  sscanf(buffer,"%d %d",&width,&height);
  rfbLog("Got width %d and height %d.\n",width,height);
  fgets(buffer,1024,in);


  paddedWidth = width;


  if(width&3)
    paddedWidth+=4-(width&3);


  rfbScreen = rfbGetScreen(&argc,argv,paddedWidth,height,8,3,3);
  if(!rfbScreen)
    return 0;
  if(argc>1)
    rfbScreen->desktopName = argv[1];
  else
    rfbScreen->desktopName = "Picture";
  rfbScreen->alwaysShared = TRUE;
  rfbScreen->kbdAddEvent = HandleKey;


  rfbScreen->httpDir = "../webclients";


  rfbScreen->frameBuffer = (char*)malloc(paddedWidth*3*height);
  fread(rfbScreen->frameBuffer,width*3,height,in);
  fclose(in);


  if(width != paddedWidth) {
    int padCount = 3*(paddedWidth - width);
    for(j=height-1;j>=0;j--) {
      memmove(rfbScreen->frameBuffer+3*paddedWidth*j,
	      rfbScreen->frameBuffer+3*width*j,
	      3*width);
      memset(rfbScreen->frameBuffer+3*paddedWidth*(j+1)-padCount,
	     0,padCount);
    }
  }


  rfbInitServer(rfbScreen);


  rfbRunEventLoop(rfbScreen,40000,FALSE);

  return(0);
}
