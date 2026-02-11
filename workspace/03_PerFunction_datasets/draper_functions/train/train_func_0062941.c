asinCmplx(Cmplx *a){
   Real *r1;
   Cmplx *z, *sqzp1, *sqzm1;
   Cmplx *c1, *c2, *c3, *c4, *c5, *c6, *c7;

   z = newCmplx();
   setCmplxCmplx(z, a);
   if(1 == cmpReal(realZero, a->re)) negEqCmplx(z);


   c1 = addCmplxReal(z, realOne);
   sqzp1 = powCmplxReal(c1, realHalf);
   freeCmplx(c1);


   c1 = subCmplxReal(z, realOne);
   sqzm1 = powCmplxReal(c1, realHalf);
   freeCmplx(c1);


   if(1 == cmpReal(realZero, sqzp1->im)) negEqCmplx(sqzp1);

   c2 = mulCmplx(sqzp1, sqzm1);
   c3 = addCmplx(c2, z);
   c4 = lnCmplx(c3);
   c5 = mulCmplx(c4, cmplxI);

   c6 = subRealCmplx(realPi2, c5);

   if(1 == cmpReal(c6->re, realPi2)){
      c7 = subRealCmplx(realPi, c6);
      freeCmplx(c6);
      c6 = c7;
   }
   r1 = negReal(realPi);
   if(-1 == cmpReal(c6->re, r1)){
      c7 = subRealCmplx(r1, c6);
      freeCmplx(c6);
      c6 = c7;
   }
   freeReal(r1);
   if(1 == cmpReal(realZero, a->re)) negEqCmplx(c6);


   freeCmplx(sqzp1);
   freeCmplx(sqzm1);
   freeCmplx(z);
   freeCmplx(c2);
   freeCmplx(c3);
   freeCmplx(c4);
   freeCmplx(c5);

   return c6;
}
