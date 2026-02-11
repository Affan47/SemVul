main(argc,argv)
  int argc;
  char *argv[];
{


FILE   *ifp;
int    i, image_size, count, n_points=1000, total;
float  *hist_data,low_thresh,high_thresh,incr,tmpf;


  if (argc<5)
  {
    printf("Usage: hist2prob <image> <size> <low_thresh> <high_thresh>\n");
    exit(1);
  }

  if ((ifp=fopen(argv[1],"rb")) == NULL)
  {
    printf("File %s isn't readable\n",argv[1]);
    exit(-1);
  }
  image_size=atoi(argv[2]);
  low_thresh=atof(argv[3]);
  high_thresh=atof(argv[4]);
  incr=(high_thresh-low_thresh)/(float)n_points;
  hist_data=(float*)malloc(image_size*sizeof(float));
  fread(hist_data,sizeof(float),image_size,ifp);

  count=0;
  for(i=0; i<image_size; i++)
    if ( (hist_data[i]>low_thresh) && (hist_data[i]<high_thresh) )
      count++;


  for(tmpf=high_thresh;tmpf>low_thresh;tmpf-=incr)
  {
    total=0;
    for(i=0; i<image_size; i++)
      if ( (hist_data[i]>tmpf) && (hist_data[i]<high_thresh) )
        total++;
    total /= 2;
    printf("%f %f\n",tmpf,log10(((float)total)/((float)count)));
  }


  return (0);
}
