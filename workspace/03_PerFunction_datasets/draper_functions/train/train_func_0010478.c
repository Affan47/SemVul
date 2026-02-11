mouseReleaseEvent( QMouseEvent *event )
{
    if ( m_hoverIndex >= 0 )
    {
        if ( m_selectable )
        {
            m_items[m_hoverIndex].m_selected = !m_items[m_hoverIndex].m_selected;
            update();
        }
        else
        {
            if ( ( event->pos() - m_dragStartPosition ).manhattanLength() > QApplication::startDragDistance() )
                return;

            qDebug() << "Opening url:" << m_items[m_hoverIndex].m_url;

            if ( !m_items[m_hoverIndex].m_url.isEmpty() )
            {
                #ifndef Q_WS_WIN
                    QDesktopServices::openUrl( QUrl::fromEncoded( m_items[m_hoverIndex].m_url.toString().toUtf8() ) );
                #else
                    QDesktopServices::openUrl( m_items[m_hoverIndex].m_url );
                #endif
            }
        }


        emit clicked( m_hoverIndex );
    }
}
