xmlSecAppDecryptFile(const char* filename) {
    xmlSecAppXmlDataPtr data = NULL;
    xmlSecEncCtx encCtx;
    clock_t start_time;
    int res = -1;

    if(filename == NULL) {
        return(-1);
    }

    if(xmlSecEncCtxInitialize(&encCtx, gKeysMngr) < 0) {
        fprintf(stderr, "Error: enc context initialization failed\n");
        return(-1);
    }
    if(xmlSecAppPrepareEncCtx(&encCtx) < 0) {
        fprintf(stderr, "Error: enc context preparation failed\n");
        goto done;
    }


    data = xmlSecAppXmlDataCreate(filename, xmlSecNodeEncryptedData, xmlSecEncNs);
    if(data == NULL) {
        fprintf(stderr, "Error: failed to load template \"%s\"\n", filename);
        goto done;
    }

    start_time = clock();
    if(xmlSecEncCtxDecrypt(&encCtx, data->startNode) < 0) {
        fprintf(stderr, "Error: failed to decrypt file\n");
        goto done;
    }
    total_time += clock() - start_time;


    if(repeats <= 1) {
        if(encCtx.resultReplaced) {
            if(xmlSecAppWriteResult(data->doc, NULL) < 0) {
                goto done;
            }
        } else {
            if(xmlSecAppWriteResult(NULL, encCtx.result) < 0) {
                goto done;
            }
        }
    }
    res = 0;

done:

    if(repeats <= 1) {
        xmlSecAppPrintEncCtx(&encCtx);
    }
    xmlSecEncCtxFinalize(&encCtx);

    if(data != NULL) {
        xmlSecAppXmlDataDestroy(data);
    }
    return(res);
}
