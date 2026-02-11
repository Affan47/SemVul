integrateGauss(WidthFunction* widthFn,
  double xlo, double xhi, double tol) {


  static double x8[4]={0.96028985649753623,
		       0.79666647741362674,
		       0.52553240991632899,
		       0.18343464249564980};
  static double w8[4]={0.10122853629037626,
		       0.22238103445337447,
		       0.31370664587788729,
		       0.36268378337836198};

  static double x16[8]={0.98940093499164993,
		       0.94457502307323258,
		       0.86563120238783174,
		       0.75540440835500303,
		       0.61787624440264375,
		       0.45801677765722739,
		       0.28160355077925891,
		       0.09501250983763744};
  static double w16[8]={0.027152459411754095,
		       0.062253523938647893,
		       0.095158511682492785,
		       0.12462897125553387,
		       0.14959598881657673,
		       0.16915651939500254,
		       0.18260341504492359,
		       0.18945061045506850};

  if (xlo == xhi) {
    cerr<<"xlo = xhi"<<endl;
    return 0.0;
  }
  if (xlo > xhi) {
    cerr<<" (integrateGauss:) -> xhi < xlo"<<endl;
    return 0.0;
  }

  double sum = 0.0;
  double c = 0.001/abs(xhi-xlo);
  double zlo = xlo;
  double zhi = xhi;

  bool nextbin = true;

  while ( nextbin ) {

    double zmi = 0.5*(zhi+zlo);
    double zmr = 0.5*(zhi-zlo);


    double s8=0.0;
    for (int i=0;i<4;i++) {
      double dz = zmr * x8[i];
      s8 += w8[i]*(widthFn->function(zmi+dz) + widthFn->function(zmi-dz));
    }
    s8 *= zmr;
    double s16=0.0;
    for (int i=0;i<8;i++) {
      double dz = zmr * x16[i];
      s16 += w16[i]*(widthFn->function(zmi+dz) + widthFn->function(zmi-dz));
    }
    s16 *= zmr;
    if (abs(s16-s8) < tol*(1+abs(s16))) {

      nextbin=true;
      sum += s16;

      zlo=zhi;
      zhi=xhi;
      if ( zlo == zhi ) nextbin = false;
    } else {

      if (1.0 + c*abs(zmr) == 1.0) {
	cerr << " (integrateGauss:) too high accuracy required"<<endl;
	sum = 0.0 ;
	break;
      }
      zhi=zmi;
      nextbin=true;
    }
  }

  return sum;
}
