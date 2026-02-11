setLocationText(const KUrl& url)
{
    if (!url.isEmpty()) {
        QPixmap mimeTypeIcon = KIconLoader::global()->loadMimeTypeIcon( KMimeType::iconNameForUrl( url ), KIconLoader::Small );
        if (url.hasPath()) {
            if (!url.directory().isEmpty())
            {
                KUrl u(url);
                u.setPath(u.directory());
                q->setUrl(u, false);
            }
            else {
                q->setUrl(url.path(), false);
            }
        }
        setDummyHistoryEntry(url.fileName() , mimeTypeIcon);
    } else {
        removeDummyHistoryEntry();
    }


    if (operationMode == KFileWidget::Saving && !locationEdit->isVisible()) {
       setNonExtSelection();
    }
}
