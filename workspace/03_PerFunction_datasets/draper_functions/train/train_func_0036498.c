eventType( const QEvent::Type& type ) const
    {
        switch( type )
        {
            case QEvent::MouseButtonPress: return "MouseButtonPress";
            case QEvent::MouseButtonRelease: return "MouseButtonRelease";
            case QEvent::MouseMove: return "MouseMove";
            default: return "Unknown";
        }
    }
