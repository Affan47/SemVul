xmlSecAppPrepareDSigCtx(xmlSecDSigCtxPtr dsigCtx) {
    if(dsigCtx == NULL) {
        fprintf(stderr, "Error: dsig context is null\n");
        return(-1);
    }


    if(xmlSecAppPrepareKeyInfoReadCtx(&(dsigCtx->keyInfoReadCtx)) < 0) {
        fprintf(stderr, "Error: failed to prepare key info context\n");
        return(-1);
    }

    if(xmlSecAppCmdLineParamGetString(&sessionKeyParam) != NULL) {
        dsigCtx->signKey = xmlSecAppCryptoKeyGenerate(xmlSecAppCmdLineParamGetString(&sessionKeyParam),
                                NULL, xmlSecKeyDataTypeSession);
        if(dsigCtx->signKey == NULL) {
            fprintf(stderr, "Error: failed to generate a session key \"%s\"\n",
                    xmlSecAppCmdLineParamGetString(&sessionKeyParam));
            return(-1);
        }
    }


    if(xmlSecAppCmdLineParamIsSet(&ignoreManifestsParam)) {
        dsigCtx->flags |= XMLSEC_DSIG_FLAGS_IGNORE_MANIFESTS;
    }
    if(xmlSecAppCmdLineParamIsSet(&storeReferencesParam)) {
        dsigCtx->flags |= XMLSEC_DSIG_FLAGS_STORE_SIGNEDINFO_REFERENCES |
                          XMLSEC_DSIG_FLAGS_STORE_MANIFEST_REFERENCES;
        print_debug = 1;
    }
    if(xmlSecAppCmdLineParamIsSet(&storeSignaturesParam)) {
        dsigCtx->flags |= XMLSEC_DSIG_FLAGS_STORE_SIGNATURE;
        print_debug = 1;
    }
    if(xmlSecAppCmdLineParamIsSet(&enableVisa3DHackParam)) {
        dsigCtx->flags |= XMLSEC_DSIG_FLAGS_USE_VISA3D_HACK;
    }

    if(xmlSecAppCmdLineParamGetStringList(&enabledRefUrisParam) != NULL) {
        dsigCtx->enabledReferenceUris = xmlSecAppGetUriType(
                    xmlSecAppCmdLineParamGetStringList(&enabledRefUrisParam));
        if(dsigCtx->enabledReferenceUris == xmlSecTransformUriTypeNone) {
            fprintf(stderr, "Error: failed to parse \"%s\"\n",
                    xmlSecAppCmdLineParamGetStringList(&enabledRefUrisParam));
            return(-1);
        }
    }

    return(0);
}
