update() {


  advance(pDozens);


  register double  y1;

  if ( endIters == 1 ) {
    y1 = randoms[ 4] - randoms[11] - carry;
    if ( y1 < 0.0 ) {
      y1 += 1.0;
      carry = twoToMinus_48();
    } else {
      carry = 0.0;
    }
    randoms[11] = randoms[10];
    randoms[10] = randoms[ 9];
    randoms[ 9] = randoms[ 8];
    randoms[ 8] = randoms[ 7];
    randoms[ 7] = randoms[ 6];
    randoms[ 6] = randoms[ 5];
    randoms[ 5] = randoms[ 4];
    randoms[ 4] = randoms[ 3];
    randoms[ 3] = randoms[ 2];
    randoms[ 2] = randoms[ 1];
    randoms[ 1] = randoms[ 0];
    randoms[ 0] = y1;

  } else {

    int m, nr, ns;
    for ( m = 0, nr = 11, ns = 4; m < endIters; ++m, --nr ) {
      y1 = randoms [ns] - randoms[nr] - carry;
      if ( y1 < 0.0 ) {
        y1 += 1.0;
        carry = twoToMinus_48();
      } else {
        carry = 0.0;
      }
      randoms[nr] = y1;
      --ns;
      if ( ns < 0 ) {
        ns = 11;
      }
    }

    double temp[12];
    for (m=0; m<12; m++) {
      temp[m]=randoms[m];
    }

    ns = 11 - endIters;
    for (m=11; m>=0; --m) {
      randoms[m] = temp[ns];
      --ns;
      if ( ns < 0 ) {
        ns = 11;
      }
    }

  }


  index = 11;

}
