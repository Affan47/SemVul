formsWithCachedData(QWebFrame* frame, bool recursive) const
{
    WebFormList list;

    if (frame) {
        list << d->parseFormData(frame);

        if (recursive) {
            QList<QWebFrame*> childFrameList;
            collectAllChildFrames(frame, childFrameList);
            QListIterator <QWebFrame *> framesIt (childFrameList);
            while (framesIt.hasNext()) {
                list << d->parseFormData(framesIt.next());
            }
        }
    }

    return list;
}
