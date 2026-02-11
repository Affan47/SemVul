addFormMenu(int formId, string_t* page)
{

    mutexLock(M_STATE);

    SingleList* list = userMenu();

    if (listSingleLength(list) > 0) {

        stringAppend(page, "Set(menu,replace");

        while(list) {
            if (list->data && ((string_t*) list->data)->str) {
                stringAppend(page, ",");
                stringAppend(page, ((string_t*) list->data)->str);
            }
            list = listSingleNext(list);
        }
        stringAppend(page, ");");
    }

    mutexUnlock(M_STATE);
}
