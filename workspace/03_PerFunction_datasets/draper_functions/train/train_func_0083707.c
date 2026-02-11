checkEssentialMimeTypes()
{
    QWriteLocker lock(&m_mutex);
    if (m_mimeTypesChecked)
        return;

    m_mimeTypesChecked = true;


    if (!checkMimeTypes()) {


        KMessage::message(KMessage::Error, i18n("No mime types installed. "
            "Check that shared-mime-info is installed, and that XDG_DATA_DIRS is not set, or includes /usr/share."));
        return;
    }

    QStringList missingMimeTypes;

    if (!KMimeType::mimeType(QLatin1String("inode/directory")))
        missingMimeTypes.append(QLatin1String("inode/directory"));
#ifndef Q_OS_WIN


    if (!KMimeType::mimeType(QLatin1String("inode/blockdevice")))
        missingMimeTypes.append(QLatin1String("inode/blockdevice"));
    if (!KMimeType::mimeType(QLatin1String("inode/chardevice")))
        missingMimeTypes.append(QLatin1String("inode/chardevice"));
    if (!KMimeType::mimeType(QLatin1String("inode/socket")))
        missingMimeTypes.append(QLatin1String("inode/socket"));
    if (!KMimeType::mimeType(QLatin1String("inode/fifo")))
        missingMimeTypes.append(QLatin1String("inode/fifo"));
#endif
    if (!KMimeType::mimeType(QLatin1String("application/x-shellscript")))
        missingMimeTypes.append(QLatin1String("application/x-shellscript"));
    if (!KMimeType::mimeType(QLatin1String("application/x-executable")))
        missingMimeTypes.append(QLatin1String("application/x-executable"));
    if (!KMimeType::mimeType(QLatin1String("application/x-desktop")))
        missingMimeTypes.append(QLatin1String("application/x-desktop"));

    if (!missingMimeTypes.isEmpty())
        errorMissingMimeTypes(missingMimeTypes);
}
