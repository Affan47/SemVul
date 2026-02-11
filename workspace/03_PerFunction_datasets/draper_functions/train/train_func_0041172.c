invReal(Real *a){
   Real *p = newReal();
   p->ok = a->ok;
   if(a->num == 0.0){
      p->ok = REAL_NAN;
      p->num = 0.0;
   } else {
      p->num = 1.0 / a->num;
      checkFinite(p);
   }

   return p;
}
