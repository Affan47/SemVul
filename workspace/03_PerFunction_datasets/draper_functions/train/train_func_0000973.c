readinframes_as_double(char *movieFile,double *stimuli, unsigned long Ntrials,int dimx, int dimy, int x0, int y0, int Nh, int Nv, int cx, int cy)
{
  int nmax,i,j,Ntcurrent=0;
  unsigned long k;
  int fsize=(int)((Nv*Nh)/(cx*cy));
  double sum;
  void erroropen(char *);

  double *b;
  double *tstpatch;

  tstpatch=dvector(0,fsize-1);
  b=dvector(0,dimx*dimy-1);

  FILE *inf;

  Patch ptc(dimx, dimy, x0-1, y0-1, Nh, Nv, cx, cy);

    inf=fopen(movieFile,"rb");
    if (inf ==NULL)  erroropen(movieFile);

	runChecks(inf, Ntrials, dimx, dimy, x0, y0, Nh, Nv, cx, cy, sizeof(double));


    for(i=1;i<=Ntrials;i++){
      fread(b,sizeof(double),dimx*dimy,inf);
      if (ferror(inf)) myerror("error reading from movie file.");
      ptc.dConvert(b,tstpatch);
      for(j=1;j<=fsize;j++){
	    stimuli[(i-1)*fsize+j]= tstpatch[j-1];
      }
    }
    fclose(inf);
  free_dvector(b,0,dimx*dimy-1);
  free_dvector(tstpatch,0,fsize-1);
}
