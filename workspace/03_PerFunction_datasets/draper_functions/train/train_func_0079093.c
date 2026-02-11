isGameFinished() const
{
    if ( m_pieces.isEmpty() || m_undoStack.isClean() )
        return true;

    for ( int j = 0; j < PHC; ++j ) {
        for ( int i = 0; i < PWC; ++i ) {
            Piece* item = m_pieces[j*PWC+i];

            if ( !item->isEnabled() )
                continue;
            int rightX = i + 1;
            int downY = j + 1;
            if ( rightX < PWC && m_pieces[j*PWC+rightX]->isEnabled()
                && m_pieces[j*PWC+rightX]->m_color == item->m_color ) {
                return false;
            }
            if ( downY < PHC && m_pieces[downY*PWC+i]->isEnabled()
                && m_pieces[downY*PWC+i]->m_color == item->m_color ) {
                return false;
            }
        }
    }
    return true;
}
