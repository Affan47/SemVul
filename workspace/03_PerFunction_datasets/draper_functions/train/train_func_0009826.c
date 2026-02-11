WMP_calc(MFCCWork *w, float *mfcc, Value *para)
{
  float energy = 0.0;
  float c0 = 0.0;
  int p;

  if (para->zmeanframe) {
    ZMeanFrame(w->bf, para->framesize);
  }

  if (para->energy && para->raw_e) {

    energy = CalcLogRawE(w->bf, para->framesize);
  }

  PreEmphasise(w->bf, para->framesize, para->preEmph);

  Hamming(w->bf, para->framesize, w);
  if (para->energy && ! para->raw_e) {

    energy = CalcLogRawE(w->bf, para->framesize);
  }

  MakeFBank(w->bf, w, para);

  if (para->c0) c0 = CalcC0(w, para);

  MakeMFCC(mfcc, para, w);

  WeightCepstrum(mfcc, para, w);

  p = para->mfcc_dim;
  if (para->c0) mfcc[p++] = c0;
  if (para->energy) mfcc[p++] = energy;
}
