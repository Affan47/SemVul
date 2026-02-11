PKIX_Shutdown(void *plContext)
{
        PKIX_List *savedPkixLoggers = NULL;
        PKIX_List *savedPkixLoggersErrors = NULL;
        PKIX_List *savedPkixLoggersDebugTrace = NULL;

        PKIX_ENTER(LIFECYCLE, "PKIX_Shutdown");

        if (!pkixIsInitialized){

                PKIX_RETURN(LIFECYCLE);
        }

        pkixIsInitialized = PKIX_FALSE;

        if (pkixLoggers) {
                savedPkixLoggers = pkixLoggers;
                savedPkixLoggersErrors = pkixLoggersErrors;
                savedPkixLoggersDebugTrace = pkixLoggersDebugTrace;
                pkixLoggers = NULL;
                pkixLoggersErrors = NULL;
                pkixLoggersDebugTrace = NULL;
                PKIX_DECREF(savedPkixLoggers);
                PKIX_DECREF(savedPkixLoggersErrors);
                PKIX_DECREF(savedPkixLoggersDebugTrace);
        }
        PKIX_DECREF(pkixLoggerLock);


        PKIX_DECREF(cachedCertSigTable);
        PKIX_DECREF(cachedCrlSigTable);
        PKIX_DECREF(cachedCertChainTable);
        PKIX_DECREF(cachedCertTable);
        PKIX_DECREF(cachedCrlEntryTable);
        PKIX_DECREF(aiaConnectionCache);
        PKIX_DECREF(httpSocketCache);


        if (pkixErrorList) {
            PKIX_PL_Object_DecRef((PKIX_PL_Object*)pkixErrorList, plContext);
            pkixErrorList = NULL;
        }

        PKIX_CHECK(PKIX_PL_Shutdown(plContext),
                PKIX_SHUTDOWNFAILED);

#ifdef PKIX_OBJECT_LEAK_TEST
        PORT_Free(fnStackInvCountArr);
        PORT_Free(fnStackNameArr);
        PL_HashTableDestroy(fnInvTable);
#endif

cleanup:

        PKIX_RETURN(LIFECYCLE);
}
