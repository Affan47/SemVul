flam3_check_unity_chaos(flam3_genome *cp) {

   int i,j;
   int num_std;
   int unity=1;
   num_std = cp->num_xforms - (cp->final_xform_index >= 0);

   for (i=0;i<num_std;i++) {
      for (j=0;j<num_std;j++) {
         if ( fabs(cp->chaos[i][j]-1.0) > EPS)
            unity=0;
      }
   }

   return(unity);
}
