dropEvent(QDropEvent* event)
{
    const KUrl::List urls = KUrl::List::fromMimeData(event->mimeData());
    if (!urls.isEmpty()) {
        setDisplayHintEnabled(DraggedHint, true);

        emit urlsDropped(m_url, event);

        setDisplayHintEnabled(DraggedHint, false);
        update();
    }
}
