enumDependencies(Item *pItem, void *context, CheckDependency check) {
    const UDataInfo *pInfo;
    const uint8_t *inBytes;
    int32_t format, length, infoLength, itemHeaderLength;
    UErrorCode errorCode;

    errorCode=U_ZERO_ERROR;
    pInfo=getDataInfo(pItem->data,pItem->length, infoLength, itemHeaderLength, &errorCode);
    if(U_FAILURE(errorCode)) {
        return;
    }


    format=getDataFormat(pInfo->dataFormat);
    if(format>=0) {
        UDataSwapper *ds;


        ds=udata_openSwapper((UBool)pInfo->isBigEndian, pInfo->charsetFamily, U_IS_BIG_ENDIAN, U_CHARSET_FAMILY, &errorCode);
        if(U_FAILURE(errorCode)) {
            fprintf(stderr, "icupkg: udata_openSwapper(\"%s\") failed - %s\n",
                    pItem->name, u_errorName(errorCode));
            exit(errorCode);
        }

        ds->printError=printError;
        ds->printErrorContext=stderr;

        inBytes=pItem->data+itemHeaderLength;
        length=pItem->length-itemHeaderLength;

        switch(format) {
        case FMT_RES:
            ures_enumDependencies(ds, pItem->name, pInfo, inBytes, length, check, context, &errorCode);
            break;
        case FMT_CNV:
            ucnv_enumDependencies(ds, pItem->name, pInfo, inBytes, length, check, context, &errorCode);
            break;
        default:
            break;
        }

        udata_closeSwapper(ds);

        if(U_FAILURE(errorCode)) {
            exit(errorCode);
        }
    }
}
