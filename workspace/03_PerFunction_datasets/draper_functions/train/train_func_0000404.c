FDKaacEnc_CalcAutoCorrValue(
        const FIXP_DBL           *spectrum,
        const INT                 startLine,
        const INT                 stopLine,
        const INT                 lag,
        const INT                 scale
        )
{
    int i;
    FIXP_DBL result = FL2FXCONST_DBL(0.f);

    if (lag==0) {
      for (i=startLine; i<stopLine; i++) {
        result += (fPow2(spectrum[i])>>scale);
      }
    }
    else {
      for (i=startLine; i<(stopLine-lag); i++) {
        result += (fMult(spectrum[i], spectrum[i+lag])>>scale);
      }
    }

    return result;
}
