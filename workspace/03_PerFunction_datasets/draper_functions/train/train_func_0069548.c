img2ric(FILE *img,format_t format,FILE *ric,int invert,int verbose) {
  gdImagePtr im = open_gdimage(img,format);
  unsigned int width = gdImageSX(im);
  unsigned int height = gdImageSY(im);
  unsigned int x,y;
  void *ric_data = NULL;

  if (verbose) {
    printf("Width:         %d\n",width);
    printf("Height:        %d\n",height);
  }


  uint8_t *bitmap = malloc(width*height);
  for (y=0;y<height;y++) {
    for (x=0;x<width;x++) {
      int color = gdImageGetPixel(im,x,y);
      bitmap[y*width+x] = (gdImageRed(im,color)+gdImageGreen(im,color)+gdImageBlue(im,color))/3;
      if (invert) bitmap[y*width+x] = 0xFF-bitmap[y*width+x];
    }
  }


  size_t size = ric_encode(&ric_data,width,height,bitmap);
  fwrite(ric_data,1,size,ric);
  free(ric_data);
  free(bitmap);
  gdImageDestroy(im);

  return 0;
}
