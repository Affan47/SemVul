eraH2fk5(double rh, double dh,
              double drh, double ddh, double pxh, double rvh,
              double *r5, double *d5,
              double *dr5, double *dd5, double *px5, double *rv5)


{
   int i;
   double pvh[2][3], r5h[3][3], s5h[3], sh[3], wxp[3], vv[3], pv5[2][3];


   eraStarpv(rh, dh, drh, ddh, pxh, rvh, pvh);


   eraFk5hip(r5h, s5h);


   for ( i = 0; i < 3; s5h[i++] /= 365.25 );


   eraRxp(r5h, s5h, sh);


   eraTrxp(r5h, pvh[0], pv5[0]);


   eraPxp(pvh[0], sh, wxp);


   eraPmp(pvh[1], wxp, vv);


   eraTrxp(r5h, vv, pv5[1]);


   eraPvstar(pv5, r5, d5, dr5, dd5, px5, rv5);

   return;

}
