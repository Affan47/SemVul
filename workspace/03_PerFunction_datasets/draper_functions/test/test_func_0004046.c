swapBackgroundColors(){
  int i,j,temp;

  for (i=0;i<width;i++)
    for (j=0;j<height;j++){
      temp=im[j*width+i].r;
      im[j*width+i].r=im[j*width+i].b;
      im[j*width+i].b=temp;
    }
}
