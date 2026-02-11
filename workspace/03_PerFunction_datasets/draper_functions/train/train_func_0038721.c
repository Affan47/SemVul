sfxhash_gunlink_node( SFXHASH *t, SFXHASH_NODE * hnode )
{
    if( t->gnode == hnode )
    {
        t->gnode = hnode->gnext;
    }


    if( t->ghead == hnode )
    {
        t->ghead = t->ghead->gnext;
        if( t->ghead )
            t->ghead->gprev = 0;
    }

    if( hnode->gprev ) hnode->gprev->gnext = hnode->gnext;
    if( hnode->gnext ) hnode->gnext->gprev = hnode->gprev;

    if( t->gtail  == hnode )
        t->gtail  =  hnode->gprev;
}
