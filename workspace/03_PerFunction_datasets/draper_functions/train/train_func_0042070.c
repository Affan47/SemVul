pkix_List_QuickSort(
        PKIX_List *fromList,
        PKIX_List_SortComparatorCallback comparator,
        PKIX_List **pSortedList,
        void *plContext)
{
        PKIX_List *sortedList = NULL;
        PKIX_List *lessList = NULL;
        PKIX_List *greaterList = NULL;
        PKIX_List *sortedLessList = NULL;
        PKIX_List *sortedGreaterList = NULL;
        PKIX_PL_Object *object = NULL;
        PKIX_PL_Object *cmpObj = NULL;
        PKIX_Int32 cmpResult = 0;
        PKIX_UInt32 size = 0;
        PKIX_UInt32 i;

        PKIX_ENTER(BUILD, "pkix_List_QuickSort");
        PKIX_NULLCHECK_THREE(fromList, comparator, pSortedList);

        PKIX_CHECK(PKIX_List_GetLength(fromList, &size, plContext),
                PKIX_LISTGETLENGTHFAILED);

        PKIX_CHECK(PKIX_List_Create(&lessList, plContext),
                    PKIX_LISTCREATEFAILED);

        PKIX_CHECK(PKIX_List_Create(&greaterList, plContext),
                    PKIX_LISTCREATEFAILED);

        PKIX_CHECK(PKIX_List_GetItem
                (fromList, 0, &object, plContext),
                PKIX_LISTGETITEMFAILED);


        for (i = 1; i < size; i++) {

                PKIX_CHECK(PKIX_List_GetItem
                        (fromList, i, &cmpObj, plContext),
                        PKIX_LISTGETITEMFAILED);

                PKIX_CHECK(comparator(object, cmpObj, &cmpResult, plContext),
                        PKIX_COMPARATORCALLBACKFAILED);

                if (cmpResult >= 0) {
                        PKIX_CHECK(PKIX_List_AppendItem
                                (lessList, cmpObj, plContext),
                                PKIX_LISTAPPENDITEMFAILED);
                } else {
                        PKIX_CHECK(PKIX_List_AppendItem
                                (greaterList, cmpObj, plContext),
                                PKIX_LISTAPPENDITEMFAILED);
                }
                PKIX_DECREF(cmpObj);
        }

        PKIX_CHECK(PKIX_List_Create(&sortedList, plContext),
                    PKIX_LISTCREATEFAILED);

        PKIX_CHECK(PKIX_List_GetLength(lessList, &size, plContext),
                PKIX_LISTGETLENGTHFAILED);

        if (size > 1) {

                PKIX_CHECK(pkix_List_QuickSort
                        (lessList, comparator, &sortedLessList, plContext),
                        PKIX_LISTQUICKSORTFAILED);

                PKIX_CHECK(pkix_List_AppendList
                        (sortedList, sortedLessList, plContext),
                        PKIX_LISTAPPENDLISTFAILED);
        } else {
                PKIX_CHECK(pkix_List_AppendList
                        (sortedList, lessList, plContext),
                        PKIX_LISTAPPENDLISTFAILED);
        }

        PKIX_CHECK(PKIX_List_AppendItem(sortedList, object, plContext),
                PKIX_LISTAPPENDFAILED);

        PKIX_CHECK(PKIX_List_GetLength(greaterList, &size, plContext),
                PKIX_LISTGETLENGTHFAILED);

        if (size > 1) {

                PKIX_CHECK(pkix_List_QuickSort
                        (greaterList, comparator, &sortedGreaterList, plContext),
                        PKIX_LISTQUICKSORTFAILED);

                PKIX_CHECK(pkix_List_AppendList
                        (sortedList, sortedGreaterList, plContext),
                        PKIX_LISTAPPENDLISTFAILED);
        } else {
                PKIX_CHECK(pkix_List_AppendList
                        (sortedList, greaterList, plContext),
                        PKIX_LISTAPPENDLISTFAILED);
        }

        *pSortedList = sortedList;

cleanup:

        PKIX_DECREF(cmpObj);
        PKIX_DECREF(object);
        PKIX_DECREF(sortedGreaterList);
        PKIX_DECREF(sortedLessList);
        PKIX_DECREF(greaterList);
        PKIX_DECREF(lessList);

        PKIX_RETURN(LIST);
}
