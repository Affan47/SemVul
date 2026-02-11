WinFirQ(float LowOmega, float UppOmega,
       float *Shape, int Len, double (*Window)(double), float shift)
{ int i; double time,phase,shape;

  for(i=0; i<Len; i++)
  { time=i+(1.0-shift)-(float)Len/2; phase=2*M_PI*time/Len;
    if(time==0) shape=0.0;
	   else shape=(-cos(UppOmega*time)+cos(LowOmega*time))/time;

    Shape[i]=(-shape)*(*Window)(phase)/M_PI; }
}
