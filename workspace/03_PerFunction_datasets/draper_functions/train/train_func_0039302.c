addErrors(const QString &o, const QStringList &err, const QString &file, const int line,  bool forceWarning)
{
    foreach(const QString &m, err)
        addError(o, m, file, line, forceWarning);
}
