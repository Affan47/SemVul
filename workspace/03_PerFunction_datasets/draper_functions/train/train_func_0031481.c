Probs(XSVector UEXSecs) {
  GSLIntegrator integrator;
  unsigned int iH(1), iS(0);
  double P(0.0);
  double P0(0.0);
  Length bmax(500.0*sqrt(millibarn));


  assert(UEXSecs.size() == 1);

  for ( XSVector::const_iterator it = UEXSecs.begin();
        it != UEXSecs.end(); ++it ) {

    iH = 0;


    Eikonalization inelint(this, -1, *it, softXSec_, softMu2_);
    inelXSec_ = integrator.value(inelint, ZERO, bmax);

    avgNhard_ = 0.0;
    avgNsoft_ = 0.0;
    bmax = 10.0*sqrt(millibarn);
    do{
      if(Algorithm()>-1 && iH==0){
	iH++;
	continue;
      }
      iS = 0;
      do{
	if( ( Algorithm() == -1 && iS==0 && iH==0 ) ){
	  iS++;
	  continue;
	}

	Eikonalization integrand(this, iH*100+iS, *it, softXSec_, softMu2_);

	if(Algorithm() > 0){
	  P = integrator.value(integrand, ZERO, bmax) / *it;
	}else{
	  P = integrator.value(integrand, ZERO, bmax) / inelXSec_;
	}

	if(Algorithm()>-1){
	  theMultiplicities.insert(P, make_pair(iH-1, iS));
	  avgNhard_ += P*(iH-1);
	}else{
	  theMultiplicities.insert(P, make_pair(iH, iS));
	  avgNhard_ += P*(iH);
	}
	avgNsoft_ += P*iS;
	if(iS==0)
	  P0 = P;

	iS++;
      } while ( (iS < maxScatters_) && (iS < 5 || P > 1.e-15 ) && softInt_ );
      iH++;
    } while ( (iH < maxScatters_) && (iH < 5 || P0 > 1.e-15) );
  }
}
