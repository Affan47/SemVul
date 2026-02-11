my_sqrt(int x){
  int y0=0,y1=x,ym;
  for (;y0<y1-1;){
    ym=(y0+y1)/2;
    if (ym*ym<x) y0=ym; else y1=ym;
  }
  return y0;
}
