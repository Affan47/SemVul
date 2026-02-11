dlist_append (DList * list, void * data)
{
    DListElement * element = _dlist_element_alloc ();
    element->data = data;
    element->next = NULL;

    list->length++;

    if (list->head == NULL) {
        list->head = list->tail = element;
        element->previous = NULL;
    } else {
        list->tail->next = element;
        element->previous = list->tail;
        list->tail = element;
    }
}
