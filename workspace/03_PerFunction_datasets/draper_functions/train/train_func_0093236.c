transition()
{

  double aa, bb, freqr, freqy, freqgr, freqty;

  freqr = freqa + freqg;
  freqy = freqc + freqt;
  freqgr = freqg / freqr;
  freqty = freqt / freqy;
  aa = ttratio * freqr * freqy - freqa * freqg - freqc * freqt;
  bb = freqa * freqgr + freqc * freqty;
  xi = aa / (aa + bb);
  xv = 1.0 - xi;
  if (xi <= 0.0 && xi >= -epsilon)
    xi = 0.0;
  if (xi < 0.0){
    printf("THIS TRANSITION-TRANSVERSION RATIO IS IMPOSSIBLE WITH");
    printf(" THESE BASE FREQUENCIES\n");
    embExitBad();}
}
