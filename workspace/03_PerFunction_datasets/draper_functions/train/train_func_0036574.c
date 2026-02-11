list_get( List *list, int pos )
{
    int i;
    List_Entry *cur = &list->head;

    if ( pos < 0 || pos >= list->count ) return 0;
    for ( i = 0; i <= pos; i++ ) cur = cur->next;
    return cur->item;
}
