blit_sgb_mask_yv12(void)
{
      int i,j;


  Uint16 *bufy=(Uint16*)overlay->pixels[0];
  Uint8 *bufu=(Uint8*)overlay->pixels[1];
  Uint8 *bufv=(Uint8*)overlay->pixels[2];
  Uint16 *nbufy=(Uint16*)overlay->pixels[0]+(overlay->pitches[0]>>1);
  Uint16 *t=sgb_buf->pixels;

  for(j=0;j<SGB_HEIGHT;j++){
    for(i=0;i<SGB_WIDTH;i++){
      nbufy[i]=bufy[i]=rgb2yuv[t[i]].y;
      bufu[i]=rgb2yuv[t[i]].u;
      bufv[i]=rgb2yuv[t[i]].v;

    }
    nbufy+=overlay->pitches[0];
    bufy+=overlay->pitches[0];
    bufu+=overlay->pitches[1];
    bufv+=overlay->pitches[2];
    t=&t[i];
  }

}
