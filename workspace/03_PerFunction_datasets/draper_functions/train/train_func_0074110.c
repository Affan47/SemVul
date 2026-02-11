update(const KUrl& srcUrl, const KUrl& destUrl)
{
    if (!canUseClipboard()) {
        return;
    }

    QClipboard* clipboard = QApplication::clipboard();
    if (clipboard->mimeData()->hasUrls()) {
        KUrl::List clipboardUrls = KUrl::List::fromMimeData(clipboard->mimeData());
        const int index = clipboardUrls.indexOf(srcUrl);
        if (index > -1) {
            clipboardUrls.replace(index, destUrl);
            QMimeData* mime = new QMimeData();
            clipboardUrls.populateMimeData(mime);
            clipboard->setMimeData(mime);
        }
    }
}
