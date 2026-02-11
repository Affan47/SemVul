eraTr(double r[3][3], double rt[3][3])


{
   double wm[3][3];
   int i, j;


   for (i = 0; i < 3; i++) {
      for (j = 0; j < 3; j++) {
         wm[i][j] = r[j][i];
      }
   }
   eraCr(wm, rt);

   return;

}
