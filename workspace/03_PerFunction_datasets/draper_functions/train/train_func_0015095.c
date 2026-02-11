DSDPGetTriDiagonalEigs(int N,double D[],double E[], double WORK[],int IIWORK[]){
  ffinteger LDZ=DSDPMax(1,N),INFO,NN=N;
  ffinteger M,IL=N-1,IU=N,*ISUPPZ=0;
  ffinteger *IWORK=(ffinteger*)IIWORK,LIWORK,LWORK;
  double WW[2],VL=-1e10,VU=1e10,*Z=0,ABSTOL=0;
  char JOBZ='N', RANGE='I';
  if (N<50){
    dstev(&JOBZ,&NN,D,E,Z,&LDZ,WORK,&INFO);
  } else {

    if (N<=1) IL=1;
    if (N<=1) IU=1;

    LWORK=20*N+1;
    LIWORK=10*N+1;

    dstevr(&JOBZ,&RANGE,&NN,D,E,&VL,&VU,&IL,&IU,&ABSTOL,&M,WW,Z,&LDZ,ISUPPZ,WORK,&LWORK,IWORK,&LIWORK,&INFO);

    if (N==1){
      D[0]=WW[0];
    } else if (N>=2){
      D[N-2]=WW[0];
      D[N-1]=WW[1];
    }

  }
  return INFO;
}
