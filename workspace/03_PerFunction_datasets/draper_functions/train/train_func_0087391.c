pkix_List_ToString(
        PKIX_PL_Object *object,
        PKIX_PL_String **pString,
        void *plContext)
{
        PKIX_List *list = NULL;
        PKIX_PL_String *listString = NULL;
        PKIX_PL_String *format = NULL;

        PKIX_ENTER(LIST, "pkix_List_ToString");
        PKIX_NULLCHECK_TWO(object, pString);

        PKIX_CHECK(pkix_CheckType(object, PKIX_LIST_TYPE, plContext),
                    PKIX_OBJECTNOTLIST);

        list = (PKIX_List *)object;

        if (!list->isHeader){
                PKIX_ERROR(PKIX_INPUTLISTMUSTBEHEADER);
        }

        PKIX_CHECK(pkix_List_ToString_Helper(list, &listString, plContext),
                    PKIX_LISTTOSTRINGHELPERFAILED);

        PKIX_CHECK(PKIX_PL_String_Create
                    (PKIX_ESCASCII, "(%s)", 0, &format, plContext),
                    PKIX_STRINGCREATEFAILED);

        PKIX_CHECK(PKIX_PL_Sprintf(pString, plContext, format, listString),
                    PKIX_SPRINTFFAILED);

cleanup:

        PKIX_DECREF(listString);
        PKIX_DECREF(format);

        PKIX_RETURN(LIST);
}
