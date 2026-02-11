dragEnterEvent(QDragEnterEvent *event)
{
    bool accept = true;


    foreach (QUrl url, event->mimeData()->urls())
        if (url.toString().startsWith("http"))
            accept = false;

    if (accept) event->acceptProposedAction();
    else event->ignore();
}
