List_getMatchedElements(List * list, List * elements, int (*isEqual)(void *, void *))
{
    ListIterator * iterator;
    ListIterator * elementsIterator;

    void * data;
    void * searchData;
    List * newList;

    if(list == NULL || elements == NULL || isEqual == NULL)
    {
        return NULL;
    }

    iterator = ListIterator_create(list);
    elementsIterator = ListIterator_create(elements);
    newList = List_create();

    data = ListIterator_seekToFirst(iterator);

    while(data != NULL)
    {
        searchData = ListIterator_seekToFirst(elementsIterator);

        while(searchData != NULL)
        {
            if(isEqual(data, searchData))
            {
                List_addBack(newList, data);
                break;
            }
            else
            {
                searchData = ListIterator_nextItem(elementsIterator);
            }
        }

        data = ListIterator_nextItem(iterator);
    }

    ListIterator_destroy(iterator);
    ListIterator_destroy(elementsIterator);

    return newList;
}
