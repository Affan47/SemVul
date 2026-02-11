AutoCorrelation(const Word16		 input[],
                            Word32       corr[],
                            Word16       samples,
                            Word16       corrCoeff) {
  Word32 i, j, isamples;
  Word32 accu;
  Word32 scf;

  scf = 10 - 1;

  isamples = samples;

  accu = 0;
  for(j=0; j<isamples; j++) {
    accu = L_add(accu, ((input[j] * input[j]) >> scf));
  }
  corr[0] = accu;


  if(corr[0] == 0) return ;


  for(i=1; i<corrCoeff; i++) {
    isamples = isamples - 1;
    accu = 0;
    for(j=0; j<isamples; j++) {
      accu = L_add(accu, ((input[j] * input[j+i]) >> scf));
    }
    corr[i] = accu;
  }
}
