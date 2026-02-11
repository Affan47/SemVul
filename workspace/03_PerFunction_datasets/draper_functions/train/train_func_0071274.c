initStkChorus(::StkFloat baseDelay, ::StkFloat depth, ::StkFloat freq, int sample_rate) {
  Chorus * ch;
  ch = new Chorus(baseDelay);
  ch->setModDepth(depth);
  ch->setModFrequency(freq);
  struct stkEffect * eff  = (struct stkEffect *) malloc(sizeof(struct stkEffect));
  Stk::setSampleRate(sample_rate);
  eff->effectPtr = ch;
  return eff;
}
