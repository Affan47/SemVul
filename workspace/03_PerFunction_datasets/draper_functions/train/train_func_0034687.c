table_add(struct SResource *table, struct SResource *res, int linenumber, UErrorCode *status) {
    struct SResource *current = NULL;
    struct SResource *prev    = NULL;
    struct SResTable *list;

    if (U_FAILURE(*status)) {
        return;
    }
    if (res == &kNoResource) {
        return;
    }


    res->line = linenumber;


    list = &(table->u.fTable);

    if(table->fType == URES_TABLE && res->fKey > 0xffff) {

        table->fType = URES_TABLE32;


        table->fSize += (1 + list->fCount) * 2;
    }

    ++(list->fCount);
    if(list->fCount > (uint32_t)list->fRoot->fMaxTableLength) {
        list->fRoot->fMaxTableLength = list->fCount;
    }


    table->fSize += table->fType == URES_TABLE ? 6 : 8;

    table->u.fTable.fChildrenSize += res->fSize + calcPadding(res->fSize);

    if (res->fType == URES_TABLE || res->fType == URES_TABLE32) {
        table->u.fTable.fChildrenSize += res->u.fTable.fChildrenSize;
    } else if (res->fType == URES_ARRAY) {
        table->u.fTable.fChildrenSize += res->u.fArray.fChildrenSize;
    }


    if (list->fFirst == NULL) {
        list->fFirst = res;
        res->fNext   = NULL;
        return;
    }

    current = list->fFirst;

    while (current != NULL) {
        if (uprv_strcmp(((list->fRoot->fKeys) + (current->fKey)), ((list->fRoot->fKeys) + (res->fKey))) < 0) {
            prev    = current;
            current = current->fNext;
        } else if (uprv_strcmp(((list->fRoot->fKeys) + (current->fKey)), ((list->fRoot->fKeys) + (res->fKey))) > 0) {

            if (prev == NULL) {

                list->fFirst = res;
            } else {

                prev->fNext = res;
            }

            res->fNext = current;
            return;
        } else {

            error(linenumber, "duplicate key '%s' in table, first appeared at line %d", list->fRoot->fKeys + current->fKey, current->line);
            *status = U_UNSUPPORTED_ERROR;
            return;
        }
    }


    prev->fNext = res;
    res->fNext  = NULL;
}
