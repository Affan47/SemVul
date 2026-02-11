xmlSecDSigReferenceCtxDebugXmlDump(xmlSecDSigReferenceCtxPtr dsigRefCtx, FILE* output) {
    xmlSecAssert(dsigRefCtx != NULL);
    xmlSecAssert(dsigRefCtx->dsigCtx != NULL);
    xmlSecAssert(output != NULL);

    if(dsigRefCtx->dsigCtx->operation == xmlSecTransformOperationSign) {
        fprintf(output, "<ReferenceCalculationContext ");
    } else {
        fprintf(output, "<ReferenceVerificationContext ");
    }
    switch(dsigRefCtx->status) {
        case xmlSecDSigStatusUnknown:
            fprintf(output, "status=\"unknown\" >\n");
            break;
        case xmlSecDSigStatusSucceeded:
            fprintf(output, "status=\"succeeded\" >\n");
            break;
        case xmlSecDSigStatusInvalid:
            fprintf(output, "status=\"invalid\" >\n");
            break;
    }

    fprintf(output, "<Id>");
    xmlSecPrintXmlString(output, dsigRefCtx->id);
    fprintf(output, "</Id>\n");

    fprintf(output, "<URI>");
    xmlSecPrintXmlString(output, dsigRefCtx->uri);
    fprintf(output, "</URI>\n");

    fprintf(output, "<Type>");
    xmlSecPrintXmlString(output, dsigRefCtx->type);
    fprintf(output, "</Type>\n");

    fprintf(output, "<ReferenceTransformCtx>\n");
    xmlSecTransformCtxDebugXmlDump(&(dsigRefCtx->transformCtx), output);
    fprintf(output, "</ReferenceTransformCtx>\n");

    if(dsigRefCtx->digestMethod != NULL) {
        fprintf(output, "<DigestMethod>\n");
        xmlSecTransformDebugXmlDump(dsigRefCtx->digestMethod, output);
        fprintf(output, "</DigestMethod>\n");
    }

    if((dsigRefCtx->result != NULL) &&
       (xmlSecBufferGetData(dsigRefCtx->result) != NULL)) {

        fprintf(output, "<Result>");
        fwrite(xmlSecBufferGetData(dsigRefCtx->result),
               xmlSecBufferGetSize(dsigRefCtx->result), 1,
               output);
        fprintf(output, "</Result>\n");
    }

    if((xmlSecDSigReferenceCtxGetPreDigestBuffer(dsigRefCtx) != NULL) &&
       (xmlSecBufferGetData(xmlSecDSigReferenceCtxGetPreDigestBuffer(dsigRefCtx)) != NULL)) {

        fprintf(output, "<PreDigestData>");
        fwrite(xmlSecBufferGetData(xmlSecDSigReferenceCtxGetPreDigestBuffer(dsigRefCtx)),
               xmlSecBufferGetSize(xmlSecDSigReferenceCtxGetPreDigestBuffer(dsigRefCtx)),
               1, output);
        fprintf(output, "</PreDigestData>\n");
    }
    if(dsigRefCtx->dsigCtx->operation == xmlSecTransformOperationSign) {
        fprintf(output, "</ReferenceCalculationContext>\n");
    } else {
        fprintf(output, "</ReferenceVerificationContext>\n");
    }
}
