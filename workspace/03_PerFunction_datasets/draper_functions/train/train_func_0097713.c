evline(GFilt g, int rno, int sno, int flag, int type,
	   double x, double y,
	   double x1, double y1, double x2, double y2)
{

  if( 0 ){
    type = type;
  }

  if( !g->shapes[sno].init ){
    g->shapes[sno].init = 1;
    g->shapes[sno].ystart = min(y1,y2);
    g->shapes[sno].ystop = max(y1,y2);
    g->shapes[sno].x1 = x1;
    g->shapes[sno].x2 = x2;
    g->shapes[sno].y1 = y1;
    if( feq(y1,y2) ){
      g->shapes[sno].xonly = 1;
      g->shapes[sno].invslope = 0;
    }
    else{
      g->shapes[sno].xonly = 0;
      g->shapes[sno].invslope = (x1 - x2) / (y1 - y2);
    }
  }
  if( (((y>=g->shapes[sno].ystart) && (y<=g->shapes[sno].ystop))		 &&
      ((!g->shapes[sno].xonly &&
       feq((((y-g->shapes[sno].y1)*g->shapes[sno].invslope)+g->shapes[sno].x1),x)) ||
      (g->shapes[sno].xonly &&
       ((x>=g->shapes[sno].x1)&&(x<=g->shapes[sno].x2))))) == flag){
    if( rno && flag ) g->rid = rno;
    return 1;
  }
  else
    return 0;
}
