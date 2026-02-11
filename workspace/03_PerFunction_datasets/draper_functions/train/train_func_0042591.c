PKIX_CertStore_Create(
        PKIX_CertStore_CertCallback certCallback,
        PKIX_CertStore_CRLCallback crlCallback,
        PKIX_CertStore_CertContinueFunction certContinue,
        PKIX_CertStore_CrlContinueFunction crlContinue,
        PKIX_CertStore_CheckTrustCallback trustCallback,
        PKIX_CertStore_ImportCrlCallback importCrlCallback,
        PKIX_CertStore_CheckRevokationByCrlCallback checkRevByCrlCallback,
        PKIX_PL_Object *certStoreContext,
        PKIX_Boolean cacheFlag,
        PKIX_Boolean localFlag,
        PKIX_CertStore **pStore,
        void *plContext)
{
        PKIX_CertStore *certStore = NULL;

        PKIX_ENTER(CERTSTORE, "PKIX_CertStore_Create");
        PKIX_NULLCHECK_THREE(certCallback, crlCallback, pStore);

        PKIX_CHECK(PKIX_PL_Object_Alloc
                    (PKIX_CERTSTORE_TYPE,
                    sizeof (PKIX_CertStore),
                    (PKIX_PL_Object **)&certStore,
                    plContext),
                    PKIX_COULDNOTCREATECERTSTOREOBJECT);

        certStore->certCallback = certCallback;
        certStore->crlCallback = crlCallback;
        certStore->certContinue = certContinue;
        certStore->crlContinue = crlContinue;
        certStore->trustCallback = trustCallback;
        certStore->importCrlCallback = importCrlCallback;
        certStore->checkRevByCrlCallback = checkRevByCrlCallback;
        certStore->cacheFlag = cacheFlag;
        certStore->localFlag = localFlag;

        PKIX_INCREF(certStoreContext);
        certStore->certStoreContext = certStoreContext;

        *pStore = certStore;
        certStore = NULL;

cleanup:

        PKIX_DECREF(certStore);

        PKIX_RETURN(CERTSTORE);
}
