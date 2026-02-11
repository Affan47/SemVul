eyes2affine(int lp)
{
  gtk_subimage_sel_t *sis= &(sp->subimasel[lp]);

  gtk_subimage_sel_t *destsis= &(sp->subimasel[MAIN_WIN]);

  double *f=sp->transforms[lp].loaded2subimage;
  double *b=sp->transforms[lp].subimage2loaded;
  double *df=sp->transforms[MAIN_WIN].loaded2subimage;


  int l,i;
  double
    de[3][2];
  double avg[2], davg[2], var[2], dvar[2], covar[2];
  for(l=0; l<3; l++) {

    affine_X_vector(&(de[l][0]),&(destsis->eyes[l][0]),df);

  }

  for(i=0; i<2; i++) {
    avg[i]=davg[i]=0;
    for(l=0; l<3; l++) {
      avg[i]+=sis->eyes[l][i];
      davg[i]+=      de[l][i];
    }
    avg[i]/=3.0; davg[i]/=3.0;
  }
  for(i=0; i<2; i++) {
    dvar[i]=var[i]=covar[i]=0;
    for(l=0; l<3; l++) {
      var[i] += SQR( sis->eyes[l][i] - avg[i] );
      dvar[i]+= SQR( de[l][i]        -davg[i] );
      covar[i]+=( sis->eyes[l][i] - avg[i] ) *( de[l][i]       -davg[i] );
    }
    var[i]/=3.0; dvar[i]/=3.0; covar[i]/=3.0;
  }
  f[0]=covar[0]/var[0];    f[4]=covar[1] / var[1];
  f[2]=davg[0]-avg[0]* f[0]; f[5]=davg[1]-avg[1]* f[4];
  invert(b,f);
}
