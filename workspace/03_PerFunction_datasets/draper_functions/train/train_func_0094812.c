_k_formatPainter(bool active)
{
    if (active) {
        painterFormat = q->currentCharFormat();
        painterActive = true;
        q->viewport()->setCursor(QCursor(KIcon("draw-brush").pixmap(32, 32), 0, 32));
    } else {
        painterFormat = QTextCharFormat();
        painterActive = false;
        q->viewport()->setCursor(Qt::IBeamCursor);
    }
}
