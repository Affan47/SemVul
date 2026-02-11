pkix_CacheCrlEntry_Lookup(
        PKIX_CertStore *store,
        PKIX_PL_X500Name *certIssuer,
        PKIX_PL_BigInt *certSerialNumber,
        PKIX_Boolean *pFound,
        PKIX_List** pCrls,
        void *plContext)
{
        PKIX_List *cachedKeys = NULL;
        PKIX_List *cachedCrlEntryList = NULL;
        PKIX_Error *cachedCrlEntryError = NULL;

        PKIX_ENTER(BUILD, "pkix_CacheCrlEntry_Lookup");
        PKIX_NULLCHECK_THREE(store, certIssuer, certSerialNumber);
        PKIX_NULLCHECK_TWO(pFound, pCrls);

        *pFound = PKIX_FALSE;


        PKIX_CHECK(PKIX_List_Create(&cachedKeys, plContext),
                    PKIX_LISTCREATEFAILED);

        PKIX_CHECK(PKIX_List_AppendItem
                    (cachedKeys, (PKIX_PL_Object *)store, plContext),
                    PKIX_LISTAPPENDITEMFAILED);

        PKIX_CHECK(PKIX_List_AppendItem
                    (cachedKeys, (PKIX_PL_Object *)certIssuer, plContext),
                    PKIX_LISTAPPENDITEMFAILED);

        PKIX_CHECK(PKIX_List_AppendItem
                    (cachedKeys,
                    (PKIX_PL_Object *)certSerialNumber,
                    plContext),
                    PKIX_LISTAPPENDITEMFAILED);

        cachedCrlEntryError = PKIX_PL_HashTable_Lookup
                    (cachedCrlEntryTable,
                    (PKIX_PL_Object *) cachedKeys,
                    (PKIX_PL_Object **) &cachedCrlEntryList,
                    plContext);
        pkix_ceLookupCount++;


        if (cachedCrlEntryList != NULL && cachedCrlEntryError == NULL ) {

                PKIX_INCREF(cachedCrlEntryList);
                *pCrls = cachedCrlEntryList;

                *pFound = PKIX_TRUE;

        } else {

                *pFound = PKIX_FALSE;
        }

cleanup:

        PKIX_DECREF(cachedKeys);
        PKIX_DECREF(cachedCrlEntryList);
        PKIX_DECREF(cachedCrlEntryError);

        PKIX_RETURN(BUILD);
}
