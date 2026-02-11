pkix_Logger_Destroy(
        PKIX_PL_Object *object,
        void *plContext)
{
        PKIX_Logger *logger = NULL;

        PKIX_ENTER(LOGGER, "pkix_Logger_Destroy");
        PKIX_NULLCHECK_ONE(object);


        PKIX_CHECK(pkix_CheckType(object, PKIX_LOGGER_TYPE, plContext),
                    PKIX_OBJECTNOTLOGGER);

        logger = (PKIX_Logger *)object;


        logger->callback = NULL;
        PKIX_DECREF(logger->context);
        logger->logComponent = (PKIX_ERRORCLASS)NULL;

cleanup:

        PKIX_RETURN(LOGGER);
}
