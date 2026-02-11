extractItem(const char *filesPath, const char *outName, int32_t idx, char outType) {
    char filename[1024];
    UDataSwapper *ds;
    FILE *file;
    Item *pItem;
    int32_t fileLength;
    uint8_t itemCharset, outCharset;
    UBool itemIsBigEndian, outIsBigEndian;

    if(idx<0 || itemCount<=idx) {
        return;
    }
    pItem=items+idx;


    if(outType!=0 && pItem->type!=outType) {

        UErrorCode errorCode=U_ZERO_ERROR;
        makeTypeProps(pItem->type, itemCharset, itemIsBigEndian);
        makeTypeProps(outType, outCharset, outIsBigEndian);
        ds=udata_openSwapper(itemIsBigEndian, itemCharset, outIsBigEndian, outCharset, &errorCode);
        if(U_FAILURE(errorCode)) {
            fprintf(stderr, "icupkg: udata_openSwapper(item %ld) failed - %s\n",
                    (long)idx, u_errorName(errorCode));
            exit(errorCode);
        }

        ds->printError=printPackageError;
        ds->printErrorContext=stderr;


        udata_swap(ds, pItem->data, pItem->length, pItem->data, &errorCode);
        if(U_FAILURE(errorCode)) {
            fprintf(stderr, "icupkg: udata_swap(item %ld) failed - %s\n", (long)idx, u_errorName(errorCode));
            exit(errorCode);
        }
        udata_closeSwapper(ds);
        pItem->type=outType;
    }


    makeFullFilenameAndDirs(filesPath, outName, filename, (int32_t)sizeof(filename));
    file=fopen(filename, "wb");
    if(file==NULL) {
        fprintf(stderr, "icupkg: unable to create file \"%s\"\n", filename);
        exit(U_FILE_ACCESS_ERROR);
    }
    fileLength=(int32_t)fwrite(pItem->data, 1, pItem->length, file);

    if(ferror(file) || fileLength!=pItem->length) {
        fprintf(stderr, "icupkg: unable to write complete file \"%s\"\n", filename);
        exit(U_FILE_ACCESS_ERROR);
    }
    fclose(file);
}
