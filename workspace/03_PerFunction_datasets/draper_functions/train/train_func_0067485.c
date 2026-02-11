sfxhash_next( SFXHASH * t )
{
    if( !t->cnode )
        return ;


    t->cnode = t->cnode->next;
    if( t->cnode )
    {
        return;
    }


    for( t->crow++; t->crow < t->nrows; t->crow++ )
    {
        t->cnode = t->table[ t->crow ];
        if( t->cnode )
        {
            return;
        }
    }
}
