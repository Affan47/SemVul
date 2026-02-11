dropEvent(QDropEvent *event)
{
    const BoardViewMimeData *mimeData = qobject_cast<const BoardViewMimeData *>(event->mimeData());
    if(mimeData)
    {
        Square s = squareAt(event->pos());
        emit pieceDropped(s, mimeData->m_piece);
        event->acceptProposedAction();
    }
}
