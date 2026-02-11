setExclusions(
    QStringList list)
{
    foreach(QString path, list)
    {
        checkPath(path, Qt::Unchecked);
    }
}
