calc_tabsize()
{
#ifdef _DEBUG
    std::cout << "TabNotebook::calc_tabsize\n";
#endif

    GtkNotebook *notebook = gobj();
    GList * children = notebook->children;

    for( int i = 0; children ; ++i, children = children->next ){

        GtkNotebookPage* page = ( GtkNotebookPage* ) children->data;
        SKELETON::TabLabel* tab = get_tablabel( i );
        if( tab ){

            int tab_x = -1;
            int tab_y = -1;
            int tab_w = -1;
            int tab_h = -1;

            if( tab->is_mapped() && page ){

                tab_x = page->allocation.x;
                tab_y = page->allocation.y;
                tab_w = page->allocation.width;
                tab_h = page->allocation.height;

                Gdk::Rectangle rect = tab->get_allocation();
                m_tab_mrg = tab_w - rect.get_width();
            }

#ifdef _DEBUG
            std::cout << "page = " << i << " x = " << tab_x << " w = " << tab_w << " mrg = " << m_tab_mrg << std::endl;
#endif
            tab->set_tab_x( tab_x );
            tab->set_tab_y( tab_y );
            tab->set_tab_width( tab_w );
            tab->set_tab_height( tab_h );
        }
    }
}
