dropEvent(QDropEvent *event)
{
    QList<QUrl> urls = event->mimeData()->urls();
    if (urls.isEmpty()) return;

    if (currentWindow != trainWindow) {

        RideImportWizard *dialog = new RideImportWizard (&urls, home, this);
        dialog->process();
    } else {
        QStringList filenames;
        for (int i=0; i<urls.count(); i++)
            filenames.append(QFileInfo(urls.value(i).toLocalFile()).absoluteFilePath());
        Library::importFiles(this, filenames);
    }
    return;
}
