FDKaacEnc_CalculateFullTonality(FIXP_DBL      *RESTRICT spectrum,
						             INT           *RESTRICT sfbMaxScaleSpec,
                                     FIXP_DBL      *RESTRICT sfbEnergyLD64,
                                     FIXP_SGL      *RESTRICT sfbTonality,
                                     INT            sfbCnt,
                                     const INT     *sfbOffset,
                                     INT            usePns)
{
  INT j;
#if defined(ARCH_PREFER_MULT_32x16)
  FIXP_SGL alpha_0 = FL2FXCONST_SGL(0.25f);
  FIXP_SGL alpha_1 = FL2FXCONST_SGL(1.0f-0.25f);
#else
  FIXP_DBL alpha_0 = FL2FXCONST_DBL(0.25f);
  FIXP_DBL alpha_1 = FL2FXCONST_DBL(1.0f-0.25f);
#endif
  INT numberOfLines = sfbOffset[sfbCnt];

  if (!usePns)
    return;

  C_ALLOC_SCRATCH_START(chaosMeasurePerLine, FIXP_DBL, (1024));

  FDKaacEnc_CalculateChaosMeasure(spectrum,
                        numberOfLines,
                        chaosMeasurePerLine);


  for (j=1;j<numberOfLines;j++) {
    FIXP_DBL tmp = fMultDiv2(alpha_1, chaosMeasurePerLine[j]);
    chaosMeasurePerLine[j] = fMultAdd(tmp, alpha_0, chaosMeasurePerLine[j-1]);
  }

  FDKaacEnc_CalcSfbTonality(spectrum,
                  sfbMaxScaleSpec,
                  chaosMeasurePerLine,
                  sfbTonality,
                  sfbCnt,
                  sfbOffset,
                  sfbEnergyLD64);

  C_ALLOC_SCRATCH_END(chaosMeasurePerLine, FIXP_DBL, (1024));
}
