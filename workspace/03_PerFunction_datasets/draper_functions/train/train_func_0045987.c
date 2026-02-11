Next()
    {
        m_it.Next();


        if ( m_it.AtEnd() )
        {
            m_curPage++;
            if ( m_curPage < m_manager->GetPageCount() )
                m_it.Init( m_manager->GetPage(m_curPage), m_flags );
        }
    }
