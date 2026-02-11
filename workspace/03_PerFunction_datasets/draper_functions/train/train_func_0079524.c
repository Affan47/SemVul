fl_clear_freelist( void )
{
    Free_List_T *cur;

    while ( fl )
    {
        fl_free( fl->io );
        cur = fl;
        fl = fl->next;
        fl_free( cur );
    }
}
