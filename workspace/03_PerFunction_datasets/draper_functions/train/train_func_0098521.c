exists(const QString &fullPath)
{
#ifdef Q_OS_WIN


    if (fullPath.endsWith(QLatin1Char('/')))
        return QDir(fullPath).exists();
    return QFileInfo(fullPath).exists();
#else
    KDE_struct_stat buff;
    QByteArray cFullPath = QFile::encodeName(fullPath);
    if (access(cFullPath, R_OK) == 0 && KDE_stat( cFullPath, &buff ) == 0) {
        if (!fullPath.endsWith(QLatin1Char('/'))) {
            if (S_ISREG( buff.st_mode ))
                return true;
        } else
            if (S_ISDIR( buff.st_mode ))
                return true;
    }
    return false;
#endif
}
