setLevelData (const QString & dir, const QString& prefix,
                                 int level, QLabel * sln)
{
    KGrLevelData d;
    QString filePath;

    IOStatus stat = io->fetchLevelData (dir, prefix, level, d, filePath);
    if (stat == OK) {

        levelLayout = d.layout;
        sln->setText ((d.name.size() > 0) ? i18n ((const char *) d.name) : "");
    }
    else {

        levelLayout = "";
        sln->setText ("");
    }
}
