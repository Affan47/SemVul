t1(Wave4 &q, Wave4 &q1, Wave4 &q2,
			   Wave4 &q3, Wave4 &q4) {

  Wave4  a1Q(q2 + q3 + q4);
  Wave4 rhoQ(q3 + q4);
  double  a1S = m2(a1Q);
  double rhoS = m2(rhoQ);


  double gM = sqrtpos(rhoM*rhoM - 4*picM*picM) * (rhoM*rhoM - 4*picM*picM)
    / rhoM;
  double dm = (rhoFormFactor1(0) - rhoFormFactor1(rhoM*rhoM) +
		 rhoM*rhoM * rhoFormFactor2(rhoM*rhoM)) / gM;
  return - a1FormFactor(a1S) / (a1D(a1S) * rhoD(rhoS)) * pow2(a1M) *
    (rhoM*rhoM + rhoM*rhoG*dm) *
    (m2(q,a1Q) *  (m2(q3,a1Q) * q4 - m2(q4,a1Q) * q3) +
     (m2(q,q4) * m2(q1,q3) - m2(q,q3) * m2(q1,q4)) * a1Q);

}
