filter_get_coef(int sections,double cutoff,double q, double gain)
{

  int nInd;

  double k    = gain;
  float *Coef = (float *)calloc(4 * sections + 1, sizeof(float));
  float *coef = Coef + 1;
  double Q    = q;
  double fc   = cutoff;
  double fs   = SAMPLE_RATE;

  double   a0, a1, a2, b0, b1, b2;


 for(nInd = 0; nInd < sections; nInd++)
    {
      a0 = ProtoCoef[nInd].a0;
      a1 = ProtoCoef[nInd].a1;
      a2 = ProtoCoef[nInd].a2;

      b0 = ProtoCoef[nInd].b0;
      b1 = ProtoCoef[nInd].b1 / Q;
      b2 = ProtoCoef[nInd].b2;
      szxform(&a0, &a1, &a2, &b0, &b1, &b2, fc, fs, &k, coef);
      coef += 4;

    }

  Coef[0] = k;
  return Coef;
}
