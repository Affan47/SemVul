PKIX_ProcessingParams_AddCertChainChecker(
        PKIX_ProcessingParams *params,
        PKIX_CertChainChecker *checker,
        void *plContext)
{
        PKIX_List *list = NULL;

        PKIX_ENTER(PROCESSINGPARAMS,
                   "PKIX_ProcessingParams_AddCertChainChecker");
        PKIX_NULLCHECK_TWO(params, checker);

        if (params->certChainCheckers == NULL) {

                PKIX_CHECK(PKIX_List_Create(&list, plContext),
                    PKIX_LISTCREATEFAILED);

                params->certChainCheckers = list;
        }

        PKIX_CHECK(PKIX_List_AppendItem
            (params->certChainCheckers, (PKIX_PL_Object *)checker, plContext),
            PKIX_LISTAPPENDITEMFAILED);

        PKIX_CHECK(PKIX_PL_Object_InvalidateCache
            ((PKIX_PL_Object *)params, plContext),
            PKIX_OBJECTINVALIDATECACHEFAILED);

        list = NULL;

cleanup:

        if (list && params) {
            PKIX_DECREF(params->certChainCheckers);
        }

        PKIX_RETURN(PROCESSINGPARAMS);
}
