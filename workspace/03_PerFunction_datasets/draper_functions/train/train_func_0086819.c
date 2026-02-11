ne(F *f,F *g){
   int c1;
   F c2, c3;

   c1 = *f<*g;
   if (*g > 0) {
     c2 = CT1;
     c3 = CT2;
   } else {
     c2 = CT2;
     c3 = CT1;
   }

   R c1&&*f<*g*c2||*f>*g*c3;
 }
