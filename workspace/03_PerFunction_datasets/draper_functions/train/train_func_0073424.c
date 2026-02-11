reset_radio( PopUP *    m,
             MenuItem * item )
{
    MenuItem **ii;

    for ( ii = m->item; ii < m->item + m->nitems; ii++ )
        if ( ( *ii )->radio == item->radio )
            ( *ii )->mode &= ~ FL_PUP_CHECK;
    item->mode |= FL_PUP_CHECK;
}
