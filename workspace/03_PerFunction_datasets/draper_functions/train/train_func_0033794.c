pkix_pl_HttpCertStoreContext_Destroy(
        PKIX_PL_Object *object,
        void *plContext)
{
        const SEC_HttpClientFcnV1 *hcv1 = NULL;
        PKIX_PL_HttpCertStoreContext *context = NULL;

        PKIX_ENTER
                (HTTPCERTSTORECONTEXT, "pkix_pl_HttpCertStoreContext_Destroy");
        PKIX_NULLCHECK_ONE(object);

        PKIX_CHECK(pkix_CheckType
                    (object, PKIX_HTTPCERTSTORECONTEXT_TYPE, plContext),
                    PKIX_OBJECTNOTANHTTPCERTSTORECONTEXT);

        context = (PKIX_PL_HttpCertStoreContext *)object;
        hcv1 = (const SEC_HttpClientFcnV1 *)(context->client);
        if (context->requestSession != NULL) {
            (*hcv1->freeFcn)(context->requestSession);
            context->requestSession = NULL;
        }
        if (context->serverSession != NULL) {
            (*hcv1->freeSessionFcn)(context->serverSession);
            context->serverSession = NULL;
        }
        if (context->path != NULL) {
            PORT_Free(context->path);
            context->path = NULL;
        }

cleanup:

        PKIX_RETURN(HTTPCERTSTORECONTEXT);
}
