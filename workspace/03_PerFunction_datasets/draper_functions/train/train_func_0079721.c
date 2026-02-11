parseConfigFiles()
{

    if (mBackend && !fileName.isEmpty()) {

        bFileImmutable = false;

        QList<QString> files;
        if (wantDefaults()) {
            if (bSuppressGlobal) {
                files = getGlobalFiles();
            } else {
                foreach (const QString& f, componentData.dirs()->findAllResources(
                                                    resourceType, fileName))
                    files.prepend(f);
            }
        } else {
            files << mBackend->filePath();
        }
        if (!isSimple())
            files = extraFiles.toList() + files;


        const QByteArray utf8Locale = locale.toUtf8();
        foreach(const QString& file, files) {
#ifndef Q_OS_WIN
            if (file == mBackend->filePath()) {
#else
            if (file.compare(mBackend->filePath(), Qt::CaseInsensitive) == 0) {
#endif
                switch (mBackend->parseConfig(utf8Locale, entryMap, KConfigBackend::ParseExpansions)) {
                case KConfigBackend::ParseOk:
                    break;
                case KConfigBackend::ParseImmutable:
                    bFileImmutable = true;
                    break;
                case KConfigBackend::ParseOpenError:
                    configState = KConfigBase::NoAccess;
                    break;
                }
            } else {
                KSharedPtr<KConfigBackend> backend = KConfigBackend::create(componentData, file);
                bFileImmutable = (backend->parseConfig(utf8Locale, entryMap,
                                        KConfigBackend::ParseDefaults|KConfigBackend::ParseExpansions)
                                  == KConfigBackend::ParseImmutable);
            }

            if (bFileImmutable)
                break;
        }
        if (componentData.dirs()->isRestrictedResource(resourceType, fileName))
            bFileImmutable = true;
    }
}
