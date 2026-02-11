PKIX_PL_Shutdown(void *plContext)
{
        PKIX_UInt32 numLeakedObjects = 0;

        PKIX_ENTER(OBJECT, "PKIX_PL_Shutdown");

        if (!pkix_pl_initialized) {

            PKIX_RETURN(OBJECT);
        }

        PR_DestroyLock(classTableLock);

        pkix_pl_HttpCertStore_Shutdown(plContext);

        numLeakedObjects = pkix_pl_lifecycle_ObjectLeakCheck(NULL);
        if (PR_GetEnv("NSS_STRICT_SHUTDOWN")) {
           PORT_Assert(numLeakedObjects == 0);
        }

        if (plContext != NULL) {
                PKIX_PL_NssContext_Destroy(plContext);
        }

        pkix_pl_initialized = PKIX_FALSE;

        PKIX_RETURN(OBJECT);
}
