set_difference( FRAME *frame, int flags )
{

    LIST* b = lol_get( frame->args, 0 );
    LIST* a = lol_get( frame->args, 1 );

    LIST* result = L0;
    LISTITER iter = list_begin( b ), end = list_end( b );
    for( ; iter != end; iter = list_next( iter ) )
    {
        if (!list_in(a, list_item(iter)))
            result = list_push_back(result, object_copy(list_item(iter)));
    }
    return result;
}
