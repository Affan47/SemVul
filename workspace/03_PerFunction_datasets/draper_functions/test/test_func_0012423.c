actions_clear()
{
    Action *action = 0;
    while ( ( action = list_dequeue( actions ) ) )
        free( action );
}
