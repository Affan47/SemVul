get_AtA_nzmax(int          ndim,
                  const int    nknot[3],
                  const int    ksp[3])
{
   int    lnknot[3], lksp[3];
   int    nzmax=0;
   int    n_knabo=0, n_jnabo=0, n_inabo=0;
   int    i=0, j=0, k=0;

   for (i=0; i<ndim; i++) {lnknot[i]=nknot[i]; lksp[i]=ksp[i];}
   for (i=ndim; i<3; i++) {lnknot[i]=1; lksp[i]=1;}

   nzmax = 0;
   for (k=0; k<lnknot[2]; k++)
   {
      n_knabo = n_nabo(k,lnknot[2],lksp[2]);
      for (j=0; j<lnknot[1]; j++)
      {
	 n_jnabo = n_nabo(j,lnknot[1],lksp[1]);
         for (i=0; i<lnknot[0]; i++)
	 {
	    n_inabo = n_nabo(i,lnknot[0],lksp[0]);
            nzmax += n_knabo*n_jnabo*n_inabo;
         }
      }
   }
   return(nzmax);
}
