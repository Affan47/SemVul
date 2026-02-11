CMN(float **mfcc, int frame_num, int dim)
{
  int i, t;
  float *mfcc_ave, *sum;

  mfcc_ave = (float *)mycalloc(dim, sizeof(float));
  sum = (float *)mycalloc(dim, sizeof(float));

  for(i = 0; i < dim; i++){
    sum[i] = 0.0;
    for(t = 0; t < frame_num; t++)
      sum[i] += mfcc[t][i];
    mfcc_ave[i] = sum[i] / frame_num;
  }
  for(t = 0; t < frame_num; t++){
    for(i = 0; i < dim; i++)
      mfcc[t][i] = mfcc[t][i] - mfcc_ave[i];
  }
  free(sum);
  free(mfcc_ave);
}
