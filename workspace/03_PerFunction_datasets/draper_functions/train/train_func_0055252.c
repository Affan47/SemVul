setRenderHint( Document::RenderHint hint, bool on )
    {
        if ( on )
            m_doc->m_hints |= hint;
        else
            m_doc->m_hints &= ~(int)hint;


        if ( m_doc->m_backend == Document::SplashBackend &&
             ( hint & ( Document::Antialiasing || Document::TextAntialiasing || Document::TextHinting ) ) )
        {
            delete m_doc->m_outputDev;
            m_doc->m_outputDev = NULL;
        }
    }
