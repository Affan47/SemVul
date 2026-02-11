viewportEvent( QEvent *e )
    {
        bool ok = QScrollArea::viewportEvent( e );

        if ( e->type() == QEvent::Resize )
        {
            QEvent event( QEvent::LayoutRequest );
            QApplication::sendEvent( contentsWidget, &event );
        }
        return ok;
    }
