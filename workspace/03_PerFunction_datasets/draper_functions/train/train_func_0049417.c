open()
{
    QFileInfo info(m_output);
    QUrl url = QUrl::fromLocalFile(info.absoluteFilePath());
    QDesktopServices::openUrl(url);
}
