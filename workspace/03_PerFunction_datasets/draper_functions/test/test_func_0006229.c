FDKaacEnc_QCNew(QC_STATE  **phQC,
                                  INT         nElements
                                 ,UCHAR*      dynamic_RAM
           )
{
  AAC_ENCODER_ERROR ErrorStatus;
  int i;

  QC_STATE* hQC = GetRam_aacEnc_QCstate();
  *phQC = hQC;
  if (hQC == NULL) {
    ErrorStatus = AAC_ENC_NO_MEMORY;
    goto QCNew_bail;
  }

  if (FDKaacEnc_AdjThrNew(&hQC->hAdjThr, nElements)) {
    ErrorStatus = AAC_ENC_NO_MEMORY;
    goto QCNew_bail;
  }

  if (FDKaacEnc_BCNew(&(hQC->hBitCounter), dynamic_RAM)) {
    ErrorStatus = AAC_ENC_NO_MEMORY;
    goto QCNew_bail;
  }

  for (i=0; i<nElements; i++) {
    hQC->elementBits[i] = GetRam_aacEnc_ElementBits(i);
    if (hQC->elementBits[i] == NULL) {
      ErrorStatus = AAC_ENC_NO_MEMORY;
      goto QCNew_bail;
    }
  }

  return AAC_ENC_OK;

QCNew_bail:
  FDKaacEnc_QCClose(phQC, NULL);
  return ErrorStatus;
}
