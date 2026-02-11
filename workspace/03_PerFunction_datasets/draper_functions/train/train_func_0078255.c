analogtv_setup_sync(analogtv_input *input, int do_cb, int do_ssavi)
{
  int i,lineno,vsync;
  signed char *sig;

  int synclevel = do_ssavi ? ANALOGTV_WHITE_LEVEL : ANALOGTV_SYNC_LEVEL;

  for (lineno=0; lineno<ANALOGTV_V; lineno++) {
    vsync=lineno>=3 && lineno<7;

    sig=input->signal[lineno];

    i=ANALOGTV_SYNC_START;
    if (vsync) {
      while (i<ANALOGTV_BP_START) sig[i++]=ANALOGTV_BLANK_LEVEL;
      while (i<ANALOGTV_H) sig[i++]=synclevel;
    } else {
      while (i<ANALOGTV_BP_START) sig[i++]=synclevel;
      while (i<ANALOGTV_PIC_START) sig[i++]=ANALOGTV_BLANK_LEVEL;
      while (i<ANALOGTV_FP_START) sig[i++]=ANALOGTV_BLACK_LEVEL;
    }
    while (i<ANALOGTV_H) sig[i++]=ANALOGTV_BLANK_LEVEL;

    if (do_cb) {

      for (i=ANALOGTV_CB_START; i<ANALOGTV_CB_START+36; i+=4) {
        sig[i+1] += ANALOGTV_CB_LEVEL;
        sig[i+3] -= ANALOGTV_CB_LEVEL;
      }
    }
  }
}
