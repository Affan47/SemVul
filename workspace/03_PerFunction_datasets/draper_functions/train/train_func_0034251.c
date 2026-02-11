largef2logp(float f, int d1, int d2)
  {
    Tracer_Plus ts("F2z::largef2logp");


    int N = 20;


    if (f<=0.0) {
      cerr << "f cannot be zero or negative!" << endl;
      return 0.0;
    }

    if (d1<=0 || d2<=0) {
      cerr << "DOFs cannot be zero or negative!" << endl;
      return 0.0;
    }

    double alpha=d1/(double)d2;
    double m=(d1+d2)/2.0;
    double n=(1-d1/2.0);
    double loggam = (d1/2.0)*(::log(d1/(double)d2)-logbeta(d2/2.0,d1/2.0));


    double top = 1.0;
    double bot = n+m-1;
    double iter = 0.0;


    for(int i = 1; i <= N; i++)
      {

		  iter = iter + top* ( std::pow( f,float(-(n+i-1)) ) / ( std::pow(alpha,double(i))*bot ) );
	top = top*(n-1+i)*(-1);
	bot = bot*(n+m-1+i);

      }


    if(iter <= 0) throw Exception("iter negative");

    float logp = loggam-(m-1)*(::log(1+alpha*f))+::log(iter);


    return logp;
  }
