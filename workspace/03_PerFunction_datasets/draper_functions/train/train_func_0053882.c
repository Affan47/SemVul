MovePointLinear(Real *lim,int points,Real *coords,
			    Real x,Real y,Real *dx,Real *dy)
{
  static int i=0;
  Real c,d;

  if(y > lim[0]  &&  y < lim[2]) {


    if(x <= coords[0]) {
      d = coords[1];
    }
    else if(x >= coords[points-2]) {
      d = coords[points-1];
    }
    else {
      i = 1;
      while(x > coords[2*i] && i < points/2-1) i++;
      c = (coords[2*i+1]-coords[2*i-1])/(coords[2*i]-coords[2*i-2]);
      d = coords[2*i-1] + c*(x-coords[2*i-2]);
    }

    if(y < lim[1])
      *dy += d*(y-lim[0])/(lim[1]-lim[0]);
    else
      *dy += d*(lim[2]-y)/(lim[2]-lim[1]);
  }
}
