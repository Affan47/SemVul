mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::MidButton) {
        const QRect bounds = d->m_toggleEditableMode->geometry();
        if (bounds.contains(event->pos())) {


            QClipboard* clipboard = QApplication::clipboard();
            const QMimeData* mimeData = clipboard->mimeData();
            if (mimeData->hasText()) {
                const QString text = mimeData->text();
                setLocationUrl(KUrl(text));
            }
        }
    }
    QWidget::mouseReleaseEvent(event);
}
