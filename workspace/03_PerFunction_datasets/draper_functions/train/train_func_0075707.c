replacedPath(const QString& text, bool replaceHome, bool replaceEnv)
{
    if (text.isEmpty())
        return text;

    KUrlCompletionPrivate::MyURL url(text, QString());
    if (!url.kurl().isLocalFile())
        return text;

    url.filter(replaceHome, replaceEnv);
    return url.dir() + url.file();
}
