aacEncClose(HANDLE_AACENCODER *phAacEncoder)
{
    AACENC_ERROR err = AACENC_OK;

    if (phAacEncoder == NULL) {
        err = AACENC_INVALID_HANDLE;
        goto bail;
    }

    if (*phAacEncoder != NULL) {
        HANDLE_AACENCODER hAacEncoder = *phAacEncoder;


       if (hAacEncoder->inputBuffer!=NULL) {
           FDKfree(hAacEncoder->inputBuffer);
           hAacEncoder->inputBuffer = NULL;
       }

       if (hAacEncoder->outBuffer) {
         FreeRam_bsOutbuffer(&hAacEncoder->outBuffer);
       }

        if (hAacEncoder->hEnvEnc) {
            sbrEncoder_Close (&hAacEncoder->hEnvEnc);
        }
        if (hAacEncoder->hAacEnc) {
            FDKaacEnc_Close (&hAacEncoder->hAacEnc);
        }

        transportEnc_Close(&hAacEncoder->hTpEnc);

        if (hAacEncoder->hMetadataEnc) {
            FDK_MetadataEnc_Close (&hAacEncoder->hMetadataEnc);
        }

        Free_AacEncoder(phAacEncoder);
    }

bail:
    return err;
}
