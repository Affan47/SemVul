setFileDateTime(const QString& file)
{
    QFileInfo info(file);
    QDateTime lm = info.lastModified();
    if(info.exists())
    {
        dateTime = lm;
    }
}
