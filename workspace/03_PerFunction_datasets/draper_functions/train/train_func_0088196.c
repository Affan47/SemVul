FDKaacEnc_TnsEncode(
        TNS_INFO* tnsInfo,
        TNS_DATA* tnsData,
        const INT numOfSfb,
        const TNS_CONFIG *tC,
        const INT lowPassLine,
        FIXP_DBL* spectrum,
        const INT subBlockNumber,
        const INT blockType
        )
{
    INT i, startLine, stopLine;

    if ( ( (blockType == SHORT_WINDOW) && (!tnsData->dataRaw.Short.subBlockInfo[subBlockNumber].tnsActive) )
      || ( (blockType != SHORT_WINDOW) && (!tnsData->dataRaw.Long.subBlockInfo.tnsActive) ) )
    {
      return 1;
    }

    startLine = (tnsData->filtersMerged) ? tC->lpcStartLine[LOFILT] : tC->lpcStartLine[HIFILT];
    stopLine  = tC->lpcStopLine;

    for (i=0; i<tnsInfo->numOfFilters[subBlockNumber]; i++) {

        INT lpcGainFactor;
        FIXP_DBL LpcCoeff[TNS_MAX_ORDER];
        FIXP_DBL workBuffer[TNS_MAX_ORDER];
        FIXP_DBL parcor_tmp[TNS_MAX_ORDER];

        FDKaacEnc_Index2Parcor(
                tnsInfo->coef[subBlockNumber][i],
                parcor_tmp,
                tnsInfo->order[subBlockNumber][i],
                tC->coefRes);

        lpcGainFactor = FDKaacEnc_ParcorToLpc(
                parcor_tmp,
                LpcCoeff,
                tnsInfo->order[subBlockNumber][i],
                workBuffer);

        FDKaacEnc_AnalysisFilter(
                &spectrum[startLine],
                stopLine - startLine,
                LpcCoeff,
                tnsInfo->order[subBlockNumber][i],
                lpcGainFactor);


        startLine = tC->lpcStartLine[LOFILT];
        stopLine  = tC->lpcStartLine[HIFILT];
    }

    return(0);

}
