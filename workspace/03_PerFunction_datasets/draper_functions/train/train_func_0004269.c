get_locked()
{
    std::list< bool > locked;

    const int pages = m_notebook->get_n_pages();
    if( pages ){
        for( int i = 0; i < pages; ++i ) locked.push_back( is_locked( i ) );
    }

    return locked;
}
