readConfig (const QString &fname)
{
    TsConfig config;

    TsConfig::iterator configGroup;
    configGroup = config.insert(QString(), TsConfigGroup());

    QFile file(fname);
    if (!file.open(QIODevice::ReadOnly)) {
        return config;
    }
    QTextStream stream(&file);
    stream.setCodec("UTF-8");
    while (!stream.atEnd()) {
        QString line = stream.readLine();
        int p1, p2;


        p1 = line.indexOf(QLatin1Char('#'));
        if (p1 >= 0) {
            line = line.left(p1);
        }
        line = line.trimmed();
        if (line.isEmpty()) {
            continue;
        }

        if (line[0] == QLatin1Char('[')) {

            p1 = 0;
            p2 = line.indexOf(QLatin1Char(']'), p1 + 1);
            if (p2 < 0) {
                continue;
            }
            QString group = line.mid(p1 + 1, p2 - p1 - 1).trimmed();
            configGroup = config.find(group);
            if (configGroup == config.end()) {

                configGroup = config.insert(group, TsConfigGroup());
            }
        } else {

            p1 = line.indexOf(QLatin1Char('='));
            if (p1 < 0) {
                continue;
            }
            QString field = line.left(p1).trimmed();
            QString value = line.mid(p1 + 1).trimmed();
            if (!field.isEmpty()) {
                (*configGroup)[field] = value;
            }
        }
    }
    file.close();

    return config;
}
