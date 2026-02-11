setThemeRelativeRootPath(const QString &relPathFromAppBinary)
{

    QString path = QDir::cleanPath(qApp->applicationDirPath() + QDir::separator() + relPathFromAppBinary);
    if (QDir(path).exists()) {
        m_AbsolutePath = path;
        Utils::Log::addMessage(this, QString("INFO: theme path set to: %1").arg(path));
    }
    else
        LOG_ERROR(Trans::ConstantTranslations::tkTr(Trans::Constants::PATH_1_DOESNOT_EXISTS).arg(relPathFromAppBinary));
}
