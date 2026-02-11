PKIX_PL_GetString(
         PKIX_UInt32 stringID,
        char *defaultString,
        PKIX_PL_String **pString,
        void *plContext)
{
        PKIX_ENTER(STRING, "PKIX_PL_GetString");
        PKIX_NULLCHECK_TWO(pString, defaultString);


        PKIX_CHECK(PKIX_PL_String_Create
                    (PKIX_ESCASCII, defaultString, 0, pString, plContext),
                    PKIX_STRINGCREATEFAILED);

cleanup:

        PKIX_RETURN(STRING);
}
