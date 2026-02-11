slot_show_tree()
{
#ifdef _DEBUG
    std::cout << "SelectListDialog::slot_show_tree\n";
#endif

    if( m_bt_show_tree.get_active() ){

        if( ! m_selectview ) m_selectview = dynamic_cast< SelectListView* > ( Gtk::manage( CORE::ViewFactory( CORE::VIEW_SELECTLIST, get_url() ) ) );
        if( m_selectview ){
            m_selectview->set_parent_win( this );
            m_selectview->copy_treestore( m_treestore );
            m_selectview->sig_close_dialog().connect( sigc::mem_fun(*this, &SelectListDialog::hide ) );

            get_vbox()->pack_start(* m_selectview );
            m_selectview->set_size_request( -1, SELECTDIAG_TREEHEIGHT );
            m_selectview->focus_view();
            show_all_children();
        }

    }
    else if( m_selectview ){
        get_vbox()->remove( *m_selectview );
        resize( get_width(), 1 );
        delete m_selectview;
        m_selectview = NULL;
    }
}
