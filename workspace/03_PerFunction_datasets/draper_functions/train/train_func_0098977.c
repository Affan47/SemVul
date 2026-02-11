init_pup( PopUP * m )
{
    m->menu_cb     = NULL;
    m->enter_cb    = m->leave_cb = NULL;
    m->w = m->h    = m->maxw = 0;
    m->nitems      = 0;
    m->title_width = 0;
    m->win         = None;
    m->gc_active   = m->gc_inactive = None;
    m->bw          = pup_bw;
    m->title       = NULL;
    m->item[ 0 ]   = NULL;
    m->padh        = PADH;
    if ( ! pup_defcursor )
        pup_defcursor = fl_get_cursor_byname( XC_sb_right_arrow );
    m->cursor      = pup_defcursor;
    m->lpad        = m->rpad = PADW;
    init_pupfont( );
    m->cellh       = pup_ascent + pup_desc + 2 * m->padh;
    m->isEntry     = 0;
    m->form        = NULL;
}
