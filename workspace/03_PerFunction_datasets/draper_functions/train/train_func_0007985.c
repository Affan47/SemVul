PKIX_ResourceLimits_Create(
        PKIX_ResourceLimits **pResourceLimits,
        void *plContext)
{
        PKIX_ResourceLimits *rLimits = NULL;

        PKIX_ENTER(RESOURCELIMITS, "PKIX_ResourceLimits_Create");
        PKIX_NULLCHECK_ONE(pResourceLimits);

        PKIX_CHECK(PKIX_PL_Object_Alloc
                    (PKIX_RESOURCELIMITS_TYPE,
                    sizeof (PKIX_ResourceLimits),
                    (PKIX_PL_Object **)&rLimits,
                    plContext),
                    PKIX_COULDNOTCREATERESOURCELIMITOBJECT);


        rLimits->maxTime = 0;
        rLimits->maxFanout = 0;
        rLimits->maxDepth = 0;
        rLimits->maxCertsNumber = 0;
        rLimits->maxCrlsNumber = 0;

        *pResourceLimits = rLimits;

cleanup:

        PKIX_RETURN(RESOURCELIMITS);

}
