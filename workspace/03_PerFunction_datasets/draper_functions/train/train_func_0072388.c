toRadixReal(Real *a){
   Real *r1;


   if(getRadixMode() == DEGREES){
      r1 = mulReal(a, real180Pi);
   } else {
      r1 = setRealReal(newReal(), a);
   }
   checkFinite(r1);

   return r1;
}
