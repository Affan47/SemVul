rotGfx() {

  short n,x,y;
  long	sx,sy,dx,dy,rx,ry,ptr,adr;
  float	ang;

  angX[0]=0;
  angY[0]=-ACCEL;


  for(n=1; n<=31; n++) {
    ptr=0;
    ang=.196349540*n;
    dx=1024*cos(ang);
    dy=1024*sin(ang);

    angX[n]=ACCEL*cos(ang+1.57079);
    angY[n]=-ACCEL*sin(ang+1.57079);

    rx=16*1024+16*(dy-dx);
    ry=16*1024+16*(-dx-dy);

    for(y=0; y<=31; y++) {
      rx-=dy;
      ry+=dx;
      for(x=0; x<=31; x++) {
	rx+=dx;
	ry+=dy;

	if ( (rx<0) || (rx>32768) || (ry<0) || (ry>32768) ) {
	  ship[0][n][ptr]=0;
	  ship[1][n][ptr]=0;
	  ship[2][n][ptr]=0;
	  ship[3][n][ptr]=0;
	  ptr++;
	}
	else {
	  adr=(rx>>10) + ((ry>>10) << 5);
	  ship[0][n][ptr]=ship[0][0][adr];
	  ship[1][n][ptr]=ship[1][0][adr];

	  ship[2][n][ptr]=ship[2][0][adr];
          ship[3][n][ptr]=ship[3][0][adr];
	  ptr++;
	}
      }
      rx-=(dx << 5);
      ry-=(dy << 5);
    }
  }
}
