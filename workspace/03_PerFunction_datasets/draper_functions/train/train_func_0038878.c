set_mode( int mode )
{
    if( mode == m_mode ) return;

#ifdef _DEBUG
    int pos = m_paned.get_position();
    int size = get_size();

    std::cout << "PaneControl::set_mode = " << mode
              << " size = " << size
              << " current_pos = " << pos
              << " pos = " << get_position() << std::endl;
#endif

    m_mode = mode;
    update_position();
    m_sig_pane_modechanged.emit( m_mode );
}
