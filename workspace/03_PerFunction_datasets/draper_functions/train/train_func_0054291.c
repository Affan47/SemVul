edit_tree()
{
    if( m_editlistwin ) m_editlistwin->present();

    else{

        m_editlistwin = new EditListWin( get_url(), get_treestore() );
        m_editlistwin->signal_hide().connect( sigc::mem_fun(*this, &BBSListViewBase::slot_hide_editlistwin ) );
        m_editlistwin->show();
    }
}
