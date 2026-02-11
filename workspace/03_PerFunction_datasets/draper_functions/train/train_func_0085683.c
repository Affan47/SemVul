loadError(QUrl url)
{
    QFileInfo fi = QFileInfo(url.toString());
    slotStatusMessage(tr("Database %1 cannot be accessed at the moment (%2).").arg(fi.fileName()).arg(url.errorString()));
}
