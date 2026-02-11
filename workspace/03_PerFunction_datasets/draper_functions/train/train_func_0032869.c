get_alloc_tab( Alloc_NoteBook& alloc )
{
    alloc.x_tab = 0;
    alloc.width_tab = 0;
    alloc.height_tab = 0;

    GtkNotebook *notebook = gobj();
    if( notebook && notebook->cur_page ){

        const int bw = get_border_width();
        const int yy = get_allocation().get_y() + bw;
        const int xx = get_allocation().get_x() + bw;

        alloc.y_tab = notebook->cur_page->allocation.y - yy;
        alloc.x_tab = notebook->cur_page->allocation.x - xx;
        alloc.width_tab = notebook->cur_page->allocation.width;
        alloc.height_tab = notebook->cur_page->allocation.height;
    }
}
