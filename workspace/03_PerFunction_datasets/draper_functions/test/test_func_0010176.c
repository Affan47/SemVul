psys_norm_sub(psys sys,Ivector norm)
  { int i,t,n;
  int m = 0;
  int tog = 0;
    n=psys_d(sys);
    FORALL_POLY(sys,
      tog=0;
      FORALL_MONO(sys,
        t=(norm(n+1))*(*psys_def(sys));
        for(i=1;i<=psys_d(sys);i++)
            t+=(*psys_exp(sys,i))*norm(i);
        *psys_def(sys)=t;
        if (tog==0) { m=t; tog=1;}
        else if (m>t) m=t;
      )
      FORALL_MONO(sys,*psys_def(sys)-=m;)
    )
    return sys;
  }
