pkix_List_Remove(
        PKIX_List *list,
        PKIX_PL_Object *object,
        void *plContext)
{
        PKIX_PL_Object *current = NULL;
        PKIX_UInt32 numEntries = 0;
        PKIX_UInt32 index = 0;
        PKIX_Boolean match = PKIX_FALSE;

        PKIX_ENTER(LIST, "pkix_List_Remove");
        PKIX_NULLCHECK_TWO(list, object);

        PKIX_CHECK(PKIX_List_GetLength(list, &numEntries, plContext),
                PKIX_LISTGETLENGTHFAILED);

        for (index = 0; index < numEntries; index++) {
                PKIX_CHECK(PKIX_List_GetItem
                        (list, index, &current, plContext),
                        PKIX_LISTGETITEMFAILED);

                if (current) {
                        PKIX_CHECK(PKIX_PL_Object_Equals
                                (object, current, &match, plContext),
                                PKIX_OBJECTEQUALSFAILED);

                        PKIX_DECREF(current);
                }

                if (match) {
                        PKIX_CHECK(PKIX_List_DeleteItem
                                (list, index, plContext),
                                PKIX_LISTDELETEITEMFAILED);
                        break;
                }
        }

cleanup:

        PKIX_DECREF(current);
        PKIX_RETURN(LIST);
}
