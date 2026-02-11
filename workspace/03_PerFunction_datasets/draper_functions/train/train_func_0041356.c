xmlSchemaItemListRemove(xmlSchemaItemListPtr list, int idx)
{
    int i;
    if ((list->items == NULL) || (idx >= list->nbItems)) {
        xmlSchemaPSimpleErr("Internal error: xmlSchemaItemListRemove, "
            "index error.\n");
        return(-1);
    }

    if (list->nbItems == 1) {

        xmlFree(list->items);
        list->items = NULL;
        list->nbItems = 0;
        list->sizeItems = 0;
    } else if (list->nbItems -1 == idx) {
        list->nbItems--;
    } else {
        for (i = idx; i < list->nbItems -1; i++)
            list->items[i] = list->items[i+1];
        list->nbItems--;
    }
    return(0);
}
