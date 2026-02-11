_ISO_2022_SafeClone(
            const UConverter *cnv,
            void *stackBuffer,
            int32_t *pBufferSize,
            UErrorCode *status)
{
    struct cloneStruct * localClone;
    UConverterDataISO2022 *cnvData;
    int32_t i, size;

    if (*pBufferSize == 0) {
        *pBufferSize = (int32_t)sizeof(struct cloneStruct);
        return NULL;
    }

    cnvData = (UConverterDataISO2022 *)cnv->extraInfo;
    localClone = (struct cloneStruct *)stackBuffer;


    uprv_memcpy(&localClone->mydata, cnvData, sizeof(UConverterDataISO2022));
    localClone->cnv.extraInfo = &localClone->mydata;
    localClone->cnv.isExtraLocal = TRUE;


    if(cnvData->currentConverter != NULL) {
        size = (int32_t)(sizeof(UConverter) + sizeof(UAlignedMemory));
        localClone->mydata.currentConverter =
            ucnv_safeClone(cnvData->currentConverter,
                            &localClone->currentConverter,
                            &size, status);
        if(U_FAILURE(*status)) {
            return NULL;
        }
    }

    for(i=0; i<UCNV_2022_MAX_CONVERTERS; ++i) {
        if(cnvData->myConverterArray[i] != NULL) {
            ucnv_incrementRefCount(cnvData->myConverterArray[i]);
        }
    }

    return &localClone->cnv;
}
