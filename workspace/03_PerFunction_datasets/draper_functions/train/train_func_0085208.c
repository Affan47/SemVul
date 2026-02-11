interp_and_convert_back(double *c, int ncps, int xfi, double cxang[4][2],
                             double cxmag[4][2], double cxtrn[4][2],double store_array[3][2]) {

   int i,col;

   double accang[2],accmag[2];
   double expmag;
   int accmode[2];

   accang[0] = 0.0;
   accang[1] = 0.0;
   accmag[0] = 0.0;
   accmag[1] = 0.0;

   accmode[0]=accmode[1]=0;


   for (col=0; col<2; col++) {
      for (i=0; i<ncps; i++) {
         if (log(cxmag[i][col])<-10)
            accmode[col]=1;
      }
   }

   for (i=0; i<ncps; i++) {
      for (col=0; col<2; col++) {

         accang[col] += c[i] * cxang[i][col];

         if (accmode[col]==0)
            accmag[col] += c[i] * log(cxmag[i][col]);
         else
            accmag[col] += c[i] * (cxmag[i][col]);


         store_array[2][col] += c[i] * cxtrn[i][col];
      }
   }


   for (col=0;col<2;col++) {
      if (accmode[col]==0)
         expmag = exp(accmag[col]);
      else
         expmag = accmag[col];

      store_array[col][0] = expmag * cos(accang[col]);
      store_array[col][1] = expmag * sin(accang[col]);
   }

}
