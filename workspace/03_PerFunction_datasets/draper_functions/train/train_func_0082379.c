MVN(float **mfcc, int frame_num, Value *para)
{
  int i, t;
  float *mfcc_mean, *mfcc_sd;
  float x;
  int basedim;

  basedim = para->mfcc_dim + (para->c0 ? 1 : 0);

  mfcc_mean = (float *)mycalloc(para->veclen, sizeof(float));
  if (para->cvn) mfcc_sd = (float *)mycalloc(para->veclen, sizeof(float));


  for(i = 0; i < para->veclen; i++){
    mfcc_mean[i] = 0.0;
    for(t = 0; t < frame_num; t++)
      mfcc_mean[i] += mfcc[t][i];
    mfcc_mean[i] /= (float)frame_num;
  }
  if (para->cvn) {

    for(i = 0; i < para->veclen; i++){
      mfcc_sd[i] = 0.0;
      for(t = 0; t < frame_num; t++) {
	x = mfcc[t][i] - mfcc_mean[i];
	mfcc_sd[i] += x * x;
      }
      mfcc_sd[i] = sqrt(mfcc_sd[i] / (float)frame_num);
    }
  }
  for(t = 0; t < frame_num; t++){
    if (para->cmn) {

      for(i = 0; i < basedim; i++) mfcc[t][i] -= mfcc_mean[i];
    }
    if (para->cvn) {

      for(i = 0; i < para->veclen; i++) mfcc[t][i] /= mfcc_sd[i];
    }
  }

  if (para->cvn) free(mfcc_sd);
  free(mfcc_mean);
}
