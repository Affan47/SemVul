render_true_N_fast(void *xim,FXuchar *img){
  register FXint x,y;
  FXTRACE((150,"True MSB/LSB N bpp render nearest\n"));
  y=0;
  do{
    x=0;
    do{
      XPutPixel(((XImage*)xim),x,y,visual->rpix[1][img[0]] | visual->gpix[1][img[1]] | visual->bpix[1][img[2]]);
      img+=4;
      }
    while(++x<width);
    }
  while(++y<height);
  }
