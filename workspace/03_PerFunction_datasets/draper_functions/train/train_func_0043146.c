overwriteUrlsInClipboard(KJob* job)
{
    CopyJob* copyJob = qobject_cast<CopyJob*>(job);
    FileCopyJob* fileCopyJob = qobject_cast<FileCopyJob*>(job);

    if (!copyJob && !fileCopyJob) {
        return;
    }

    KUrl::List newUrls;

    if (copyJob) {
        Q_FOREACH(const KUrl& url, copyJob->srcUrls()) {
            KUrl dUrl = copyJob->destUrl();
            dUrl.addPath(url.fileName());
            newUrls.append(dUrl);
        }
    } else if (fileCopyJob) {
        newUrls << fileCopyJob->destUrl();
    }

    QMimeData* mime = new QMimeData();
    newUrls.populateMimeData(mime);
    QApplication::clipboard()->setMimeData(mime);
}
