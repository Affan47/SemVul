MakeMFCC(float *mfcc, Value *para, MFCCWork *w)
{
#ifdef MFCC_SINCOS_TABLE
  int i, j, k;
  k = 0;

  for(i = 0; i < para->mfcc_dim; i++){
    mfcc[i] = 0.0;
    for(j = 1; j <= para->fbank_num; j++)
      mfcc[i] += w->fbank[j] * w->costbl_makemfcc[k++];
    mfcc[i] *= w->sqrt2var;
  }
#else
  int i, j;
  float B, C;

  B = PI / para->fbank_num;

  for(i = 1; i <= para->mfcc_dim; i++){
    mfcc[i - 1] = 0.0;
    C = i * B;
    for(j = 1; j <= para->fbank_num; j++)
      mfcc[i - 1] += w->fbank[j] * cos(C * (j - 0.5));
    mfcc[i - 1] *= w->sqrt2var;
  }
#endif
}
