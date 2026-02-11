find_bounce(jugglestruct *sp,
			double yo, double yf, double yc, double tc, double cor)
{
  double tb, i, dy = 0;
  const double e = 1;


  tb = tc;
  for(i = tc / 2; i > 0.0001; i/=2){
	double dt, yt;
	if(tb == 0){
	  (void) fprintf(stderr, "juggle: bounce div by zero!\n");
	  break;
	}
	dy = (yf - yo)/tb + sp->Gr/2*tb;
	dt = tc - tb;
	yt = -cor*dy*dt + sp->Gr/2*dt*dt + yf;
	if(yt < yc + e){
	  tb-=i;
	}else if(yt > yc - e){
	  tb+=i;
	}else{
	  break;
	}
  }
  if(dy*THROW_CATCH_INTERVAL < -200) {
	tb = -1;
  }
  return tb;
}
