splat(double*args)

{
  int i=(int)args[0],j=(int)args[1],d=(int)args[2],x,y;
  for(x=0;x<NN;x++)
    buf[x]=90;
  printf("splat x=%d y=%d d=%d\n",i,j,d);
  fflush(stdout);
  for(y=-d;y<=d;y++)
    for(x=-d;x<=d;x++){
      int xx=x+i,yy=y+j;
      if((0<=xx) && (xx<N) && (0<=yy) && (yy<N))
	buf[xx+N*yy]=4095;
    }
  return img(0);
}
