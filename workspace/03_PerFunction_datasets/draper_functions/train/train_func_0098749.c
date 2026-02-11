make0sort( TARGETS * chain )
{
    PROFILE_ENTER( MAKE_MAKE0SORT );

    TARGETS * result = 0;


    while ( chain )
    {
        TARGETS * c = chain;
        TARGETS * s = result;

        chain = chain->next;


        while ( s && ( s->target->time > c->target->time ) )
            s = s->next;


        c->next = s;
        if ( result == s ) result = c;
        if ( !s ) s = result;
        if ( result != c ) s->tail->next = c;
        c->tail = s->tail;
        s->tail = c;
    }

    PROFILE_EXIT( MAKE_MAKE0SORT );
    return result;
}
