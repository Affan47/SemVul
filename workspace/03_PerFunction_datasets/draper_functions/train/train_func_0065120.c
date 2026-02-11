mouseMatch( const MousePattern &pattern,
    const QMouseEvent *event ) const
{
    if ( event->button() != pattern.button )
        return false;

    const bool matched =
        ( event->modifiers() & Qt::KeyboardModifierMask ) ==
            ( int )( pattern.state & Qt::KeyboardModifierMask );

    return matched;
}
