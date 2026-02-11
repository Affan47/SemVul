removeDir(const QString &name, QString *error)
{
    error->clear();
    QDir dir(name);
    if (!dir.exists()) {
        return true;
    }

    QStringList list = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    if (list.count()) {
        error->append(Trans::ConstantTranslations::tkTr(Trans::Constants::PATH_1_CONTAINS_DIRS).arg(name));
        return false;
    }

    list = dir.entryList(QDir::Files | QDir::NoDotAndDotDot);
    foreach(const QString &f, list) {
        if (!dir.remove(f)) {
            error->append(Trans::ConstantTranslations::tkTr(Trans::Constants::FILE_1_CANNOT_BE_REMOVED).arg(f));
            return false;
        }
    }

    if (!dir.rmpath(dir.absolutePath())) {
        error->append(Trans::ConstantTranslations::tkTr(Trans::Constants::PATH_1_CANNOT_BE_REMOVED).arg(dir.absolutePath()));
        return false;
    }
    return true;
}
