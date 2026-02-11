fl_setpup_leavecb( int            nm,
                   FL_PUP_LEAVECB cb,
                   void *         data )
{
    FL_PUP_LEAVECB oldcb;
    PopUP *m;
    int n,
        subm;

    if ( nm < 0 || nm >= fl_maxpup || ! menu_rec[ nm ].used )
        return NULL;

    m = menu_rec + nm;
    oldcb = m->leave_cb;
    m->leave_cb = cb;
    m->leave_data = data;
    for ( n = 0; n < m->nitems; n++ )
        if ( ( subm = m->item[ n ]->subm ) >= 0 && ! menu_rec[ subm ].enter_cb )
            fl_setpup_leavecb( subm, cb, data );

    return oldcb;
}
