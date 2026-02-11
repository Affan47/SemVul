correctPathCase(const QString& path, QString &corrected)
{

    if (QFile::exists(path)) {
        corrected = path;
        return true;
    }


    QStringList components = QString(path).split(QDir::separator());

    if (components.size() < 1) {
        return false;
    }

    const bool mustBeDir = components.back().isEmpty();


    if (mustBeDir) {
        components.pop_back();
    }

    if (components.isEmpty()) {
        return true;
    }

    QString correctPath;
    const unsigned initialComponents = components.size();
    for (unsigned i = 0; i < initialComponents - 1; i ++) {
        const QString tmp = components[0] + QDir::separator() + components[1];

        if (!correctLastComponentCase(tmp, correctPath, components.size() > 2 || mustBeDir)) {

            return false;
        }

        components.removeFirst();
        components[0] = correctPath;
    }

    corrected = correctPath;
    return true;
}
