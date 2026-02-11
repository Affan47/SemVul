getinput(void)
{

  inputoptions();
  if ((!freqsfrom) && !logdet && !similarity) {
    if (kimura || jukes) {
      freqa = 0.25;
      freqc = 0.25;
      freqg = 0.25;
      freqt = 0.25;
    }
    getbasefreqs(freqa, freqc, freqg, freqt, &freqr, &freqy, &freqar, &freqcy,
                   &freqgr, &freqty, &ttratio, &xi, &xv, &fracchange,
                   freqsfrom, printdata);
    if (freqa < 0.00000001) {
      freqa = 0.000001;
      freqc = 0.999999*freqc;
      freqg = 0.999999*freqg;
      freqt = 0.999999*freqt;
    }
    if (freqc < 0.00000001) {
      freqa = 0.999999*freqa;
      freqc = 0.000001;
      freqg = 0.999999*freqg;
      freqt = 0.999999*freqt;
    }
    if (freqg < 0.00000001) {
      freqa = 0.999999*freqa;
      freqc = 0.999999*freqc;
      freqg = 0.000001;
      freqt = 0.999999*freqt;
    }
    if (freqt < 0.00000001) {
      freqa = 0.999999*freqa;
      freqc = 0.999999*freqc;
      freqg = 0.999999*freqg;
      freqt = 0.000001;
    }
  }
  if (!justwts || firstset)
    seq_inputdata(seqsets[ith-1],sites);
  makeweights();
  dnadist_makevalues();
  if (freqsfrom) {
    dnadist_empiricalfreqs();
    getbasefreqs(freqa, freqc, freqg, freqt, &freqr, &freqy, &freqar, &freqcy,
                   &freqgr, &freqty, &ttratio, &xi, &xv, &fracchange,
                   freqsfrom, printdata);
  }
}
