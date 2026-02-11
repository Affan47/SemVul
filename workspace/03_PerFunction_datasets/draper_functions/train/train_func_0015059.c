deleteListCache() const
{

    QDir cacheDir(QString("%1/%2").arg(glossaryPath(), GLOSSARY_CACHELIST_PATH));
    if (cacheDir.exists()) {
        QStringList list = cacheDir.entryList(QStringList() << "*" , QDir::Files);
        int n = 0;
        for (int i = 0; i < list.size(); ++i) {
            if (QFile(cacheDir.path() + QDir::separator() + list.at(i)).remove())
                ++n;
        }
        if (n == list.count())
            return true;
    }
    return false;
}
