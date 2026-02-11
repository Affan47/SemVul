pkix_pl_X500Name_GetDERName(
        PKIX_PL_X500Name *xname,
        PLArenaPool *arena,
        SECItem **pDERName,
        void *plContext)
{
        SECItem *derName = NULL;

        PKIX_ENTER(X500NAME, "pkix_pl_X500Name_GetDERName");

        PKIX_NULLCHECK_THREE(xname, arena, pDERName);


        if (xname->derName.data == NULL) {
            *pDERName = NULL;
            goto cleanup;
        }

        derName = SECITEM_ArenaDupItem(arena, &xname->derName);
        if (derName == NULL) {
            PKIX_ERROR(PKIX_OUTOFMEMORY);
        }

        *pDERName = derName;
cleanup:

        PKIX_RETURN(X500NAME);
}
