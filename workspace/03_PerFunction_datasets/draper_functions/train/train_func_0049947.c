tenCalcOneTensor2(float tens[7], float chan[7],
                  float thresh, float slope, float b) {
  double c[7], sum, d1, d2, d3, d4, d5, d6;

  c[0] = AIR_MAX(chan[0], 1);
  c[1] = AIR_MAX(chan[1], 1);
  c[2] = AIR_MAX(chan[2], 1);
  c[3] = AIR_MAX(chan[3], 1);
  c[4] = AIR_MAX(chan[4], 1);
  c[5] = AIR_MAX(chan[5], 1);
  c[6] = AIR_MAX(chan[6], 1);
  sum = c[1] + c[2] + c[3] + c[4] + c[5] + c[6];
  tens[0] = AIR_CAST(float, (1 + airErf(slope*(sum - thresh)))/2.0);
  d1 = (log(c[0]) - log(c[1]))/b;
  d2 = (log(c[0]) - log(c[2]))/b;
  d3 = (log(c[0]) - log(c[3]))/b;
  d4 = (log(c[0]) - log(c[4]))/b;
  d5 = (log(c[0]) - log(c[5]))/b;
  d6 = (log(c[0]) - log(c[6]))/b;
  tens[1] =  AIR_CAST(float, d1);
  tens[2] =  AIR_CAST(float, d6 - (d1 + d2)/2);
  tens[3] =  AIR_CAST(float, d5 - (d1 + d3)/2);
  tens[4] =  AIR_CAST(float, d2);
  tens[5] =  AIR_CAST(float, d4 - (d2 + d3)/2);
  tens[6] =  AIR_CAST(float, d3);
  return;
}
