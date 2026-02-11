FDKaacEnc_updateUsedDynBits(INT*               sumDynBitsConsumed,
                                            QC_OUT_ELEMENT*    qcElement[(6)],
                                            CHANNEL_MAPPING*   cm)
{
  INT i;

  *sumDynBitsConsumed = 0;

  for (i=0; i<cm->nElements; i++)
  {
      ELEMENT_INFO elInfo = cm->elInfo[i];

      if ((elInfo.elType == ID_SCE) || (elInfo.elType == ID_CPE) ||
          (elInfo.elType == ID_LFE))
      {

          *sumDynBitsConsumed  += qcElement[i]->dynBitsUsed;
      }

  }

  return AAC_ENC_OK;
}
