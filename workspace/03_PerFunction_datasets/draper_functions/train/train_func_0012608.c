parseGlobFile(QIODevice* file, Format format, AllGlobs& globs)
{
    if (!file->open(QIODevice::ReadOnly))
        return false;


    const bool caseSensitiveHackNeeded = (KMimeType::sharedMimeInfoVersion() <= KDE_MAKE_VERSION(0, 60, 0));

    QTextStream stream(file);

    QString lastMime, lastPattern;
    QString line;
    while (!stream.atEnd()) {
        line = stream.readLine();
        if (line.isEmpty() || line.startsWith(QLatin1Char('#')))
            continue;

        const QStringList fields = line.split(QLatin1Char(':'), QString::KeepEmptyParts);
        if (fields.count() < 2)
            continue;


        QString mimeTypeName, pattern;
        QStringList flagList;
        int weight = 50;
        if (format == Globs2WithWeight) {
            if (fields.count() < 3)
                continue;
            weight = fields[0].toInt();
            mimeTypeName = fields[1];
            pattern = fields[2];
            const QString flagsStr = fields.value(3);
            flagList = flagsStr.split(QLatin1Char(','), QString::SkipEmptyParts);
        } else {
            mimeTypeName = fields[0];
            pattern = fields[1];
        }
        Q_ASSERT(!pattern.isEmpty());
        Q_ASSERT(!pattern.contains(QLatin1Char(':')));


        if (lastMime == mimeTypeName && lastPattern == pattern) {


            continue;
        }

        bool caseSensitive = flagList.contains(QLatin1String("cs"));

        if (caseSensitiveHackNeeded && (pattern == QLatin1String("*.C") || pattern == QLatin1String("*.c") || pattern == QLatin1String("core")))
            caseSensitive = true;

        if (pattern == QLatin1String("__NOGLOBS__")) {

            globs.removeMime(mimeTypeName);
            lastMime.clear();
        } else {
            int flags = 0;
            if (caseSensitive)
                flags = KMimeTypeRepository::CaseSensitive;


            globs.addGlob(Glob(mimeTypeName, weight, pattern, flags));
            lastMime = mimeTypeName;
            lastPattern = pattern;
        }
    }
    return true;
}
