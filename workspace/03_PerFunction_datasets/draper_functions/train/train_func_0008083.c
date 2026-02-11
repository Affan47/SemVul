restoreScrollBarState()
  {
    if ( !m_scrollArea )
      return;

    if ( m_horizontalScrollBarValue >= 0 && m_horizontalScrollBarValue <= m_scrollArea->horizontalScrollBar()->maximum() ) {
      m_scrollArea->horizontalScrollBar()->setValue( m_horizontalScrollBarValue );
      m_horizontalScrollBarValue = -1;
    }
    if ( m_verticalScrollBarValue >= 0 && m_verticalScrollBarValue <= m_scrollArea->verticalScrollBar()->maximum() ) {
      m_scrollArea->verticalScrollBar()->setValue( m_verticalScrollBarValue );
      m_verticalScrollBarValue = -1;
    }
  }
