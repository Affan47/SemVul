pkix_pl_String_ToString(
        PKIX_PL_Object *object,
        PKIX_PL_String **pString,
        void *plContext)
{
        PKIX_PL_String *string = NULL;
        char *ascii = NULL;
        PKIX_UInt32 length;

        PKIX_ENTER(STRING, "pkix_pl_String_ToString");
        PKIX_NULLCHECK_TWO(object, pString);

        PKIX_CHECK(pkix_CheckType(object, PKIX_STRING_TYPE, plContext),
                    PKIX_ARGUMENTNOTSTRING);

        string = (PKIX_PL_String*)object;

        PKIX_CHECK(PKIX_PL_String_GetEncoded
                (string, PKIX_ESCASCII, (void **)&ascii, &length, plContext),
                PKIX_STRINGGETENCODEDFAILED);

        PKIX_CHECK(PKIX_PL_String_Create
                    (PKIX_ESCASCII, ascii, 0, pString, plContext),
                    PKIX_STRINGCREATEFAILED);

        goto cleanup;

cleanup:

        PKIX_FREE(ascii);

        PKIX_RETURN(STRING);
}
