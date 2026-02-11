PKIX_ComCertSelParams_AddSubjAltName(
        PKIX_ComCertSelParams *params,
        PKIX_PL_GeneralName *name,
        void *plContext)
{
        PKIX_List *list = NULL;

        PKIX_ENTER(COMCERTSELPARAMS, "PKIX_ComCertSelParams_AddSubjAltName");
        PKIX_NULLCHECK_TWO(params, name);

        if (params->subjAltNames == NULL) {
                PKIX_CHECK(PKIX_List_Create(&list, plContext),
                        PKIX_LISTCREATEFAILED);
                params->subjAltNames = list;
        }

        PKIX_CHECK(PKIX_List_AppendItem
                    (params->subjAltNames, (PKIX_PL_Object *)name, plContext),
                    PKIX_LISTAPPENDITEMFAILED);

cleanup:

        PKIX_RETURN(COMCERTSELPARAMS)
}
