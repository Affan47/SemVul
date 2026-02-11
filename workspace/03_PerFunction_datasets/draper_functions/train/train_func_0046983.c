setPaused( bool isPaused )
{
    if ( m_isPaused == isPaused )
        return;

    m_isPaused = isPaused;


    for ( int j = 0; j < PHC; ++j ) {
        for ( int i = 0; i < PWC; ++i ) {
            Piece* item = m_pieces[j*PWC+i];
            if ( item->isEnabled() )
                item->setVisible( !m_isPaused );
        }
    }

    if ( m_isPaused ) {
        m_messenger->showMessage( i18n( "paused" ), KGamePopupItem::Center );
        emit canUndoChanged( false );
        emit canRedoChanged( false );
    }
    else {
        m_messenger->forceHide();
        emit canUndoChanged( m_undoStack.canUndo() );
        emit canRedoChanged( m_undoStack.canRedo() );
    }
}
