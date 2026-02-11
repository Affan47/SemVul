_k_openFile()
{
    QProcess::startDetached("kde-open", QStringList() << location.prettyUrl());
}
