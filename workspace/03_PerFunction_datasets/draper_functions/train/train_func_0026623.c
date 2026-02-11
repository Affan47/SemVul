MovePointAngle(Real *lim,int points,Real *coords,
			   Real x,Real y,Real *dx,Real *dz)
{
  static int i=0;
  Real c,d,x1,y1,z1,degs;

  degs = FM_PI/180.0;
  x1 = z1 = 0.0;

  if(y > lim[0]  &&  y < lim[2]) {
    if(x <= coords[0]) {
      x1 = x;
    }
    else {
      i = 1;
      while(x > coords[2*i] && i <= points/2-1) {
	x1 = x1 + cos(degs*coords[2*i-1])*(coords[2*i]-coords[2*i-2]);
	z1 = z1 + sin(degs*coords[2*i-1])*(coords[2*i]-coords[2*i-2]);
	i++;
      }
      x1 = x1 + cos(degs*coords[2*i-1])*(x-coords[2*i-2]);
      z1 = z1 + sin(degs*coords[2*i-1])*(x-coords[2*i-2]);
    }

    if(y < lim[1]) {
      *dx += (x1-x)*(y-lim[0])/(lim[1]-lim[0]);
      *dz += z1*(y-lim[0])/(lim[1]-lim[0]);
    }
    else {
      *dx += (x1-x)*(lim[2]-y)/(lim[2]-lim[1]);
      *dz += z1*(lim[2]-y)/(lim[2]-lim[1]);
    }
  }
}
