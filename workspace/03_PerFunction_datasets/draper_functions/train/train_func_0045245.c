checkPivot(double saveFromU,
				 double oldPivot) const
{
  int status;
  if ( fabs ( saveFromU ) > 1.0e-8 ) {
    double checkTolerance;

    if ( numberRowsExtra_ < numberRows_ + 2 ) {
      checkTolerance = 1.0e-5;
    } else if ( numberRowsExtra_ < numberRows_ + 10 ) {
      checkTolerance = 1.0e-6;
    } else if ( numberRowsExtra_ < numberRows_ + 50 ) {
      checkTolerance = 1.0e-8;
    } else {
      checkTolerance = 1.0e-10;
    }
    checkTolerance *= relaxCheck_;
    if ( fabs ( 1.0 - fabs ( saveFromU / oldPivot ) ) < checkTolerance ) {
      status = 0;
    } else {
#if COIN_DEBUG
      std::cout <<"inaccurate pivot "<< oldPivot << " "
		<< saveFromU << std::endl;
#endif
      if ( fabs ( fabs ( oldPivot ) - fabs ( saveFromU ) ) < 1.0e-12 ||
        fabs ( 1.0 - fabs ( saveFromU / oldPivot ) ) < 1.0e-8 ) {
        status = 1;
      } else {
        status = 2;
      }
    }
  } else {

    status = 2;
#if COIN_DEBUG
    std::cout <<"inaccurate pivot "<< saveFromU / oldPivot
	      << " " << saveFromU << std::endl;
#endif
  }
  return status;
}
