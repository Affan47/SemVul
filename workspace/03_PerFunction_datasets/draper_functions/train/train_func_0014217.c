list_dequeue( List *list )
{
    void *item;
    if ( list->count > 0 ) {
        item = list->head.next->item;
        list_delete_pos( list, 0 );
        return item;
    }
    else
        return 0;
}
