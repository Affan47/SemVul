initialize()
{
    if (d->_initialized)
        return true;


    if (!QFileInfo(d->pdfTkPath()).exists())
        return false;


    QString pdfTk = d->pdfTkPath();
    if (Utils::isRunningOnMac()) {
        if (Utils::fileMd5(pdfTk) != ::MAC_MD5
                || Utils::fileSha1(pdfTk) != ::MAC_SHA1
        #if QT_VERSION >= 0x050000
                || Utils::fileSha256(pdfTk) != ::MAC_SHA256
        #endif
                ) {
            LOG_ERROR("Wrong pdftk binary");
            return false;
        }
    } else if (Utils::isRunningOnWin()) {

        if (Utils::fileMd5(pdfTk) != ::XP_MD5
                || Utils::fileSha1(pdfTk) != ::XP_SHA1
        #if QT_VERSION >= 0x050000
                || Utils::fileSha256(pdfTk) != ::XP_SHA256
        #endif
                ) {
            LOG_ERROR("Wrong pdftk binary");
            return false;
        }
    } else if (Utils::isRunningOnLinux()) {

    }


    QFile file(pdfTk);
    if (Utils::isRunningOnMac()) {


        if (!file.permissions().testFlag(QFile::ExeOwner)
                || !file.permissions().testFlag(QFile::ExeGroup)
                || !file.permissions().testFlag(QFile::ExeUser)
                || !file.permissions().testFlag(QFile::ExeOther)) {
            file.setPermissions(QFile::ReadOwner | QFile::ExeOwner | QFile::ReadUser | QFile::ExeUser | QFile::ReadGroup | QFile::ExeGroup | QFile::ReadOther |  QFile::ExeOther);
        }
    }
    d->_initialized = true;
    return true;
}
