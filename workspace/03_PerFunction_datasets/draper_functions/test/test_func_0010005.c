FDK_MetadataEnc_Open(
        HANDLE_FDK_METADATA_ENCODER *phMetaData
        )
{
    FDK_METADATA_ERROR err = METADATA_OK;
    HANDLE_FDK_METADATA_ENCODER hMetaData = NULL;

    if (phMetaData == NULL) {
      err = METADATA_INVALID_HANDLE;
      goto bail;
    }


    hMetaData = (HANDLE_FDK_METADATA_ENCODER) FDKcalloc(1, sizeof(FDK_METADATA_ENCODER) );

    if (hMetaData == NULL) {
      err = METADATA_MEMORY_ERROR;
      goto bail;
    }

    FDKmemclear(hMetaData, sizeof(FDK_METADATA_ENCODER));


    if (FDK_DRC_Generator_Open(&hMetaData->hDrcComp)!=0) {
      err = METADATA_MEMORY_ERROR;
      goto bail;
    }


    *phMetaData = hMetaData;

    return err;

bail:
    FDK_MetadataEnc_Close(&hMetaData);
    return err;
}
