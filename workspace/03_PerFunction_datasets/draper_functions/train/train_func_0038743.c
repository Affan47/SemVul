pkix_CacheCrlEntry_Add(
        PKIX_CertStore *store,
        PKIX_PL_X500Name *certIssuer,
        PKIX_PL_BigInt *certSerialNumber,
        PKIX_List* crls,
        void *plContext)
{
        PKIX_List *cachedKeys = NULL;
        PKIX_Error *cachedCrlEntryError = NULL;

        PKIX_ENTER(BUILD, "pkix_CacheCrlEntry_Add");
        PKIX_NULLCHECK_THREE(store, certIssuer, certSerialNumber);
        PKIX_NULLCHECK_ONE(crls);


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

        cachedCrlEntryError = PKIX_PL_HashTable_Add
                    (cachedCrlEntryTable,
                    (PKIX_PL_Object *) cachedKeys,
                    (PKIX_PL_Object *) crls,
                    plContext);
        pkix_ceAddCount++;

cleanup:

        PKIX_DECREF(cachedKeys);
        PKIX_DECREF(cachedCrlEntryError);

        PKIX_RETURN(BUILD);
}
