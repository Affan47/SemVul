grepHelper(const QString& path, const QByteArray& grepValue)
{
    QFile file(path);

    if (file.exists()) {
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QByteArray line = file.readLine();
            while(!line.isNull()) {
                if (line.startsWith(grepValue)) {
                    line.remove(0, grepValue.length());
                    return line.trimmed();
                }
                line = file.readLine();
            }
        } else {
            qDebug() << "grepHelper: Cannot open file: " << path;
        }
    } else {
        qDebug() << "grepHelper: File does not exists: " << path;
    }

    return QByteArray();
}
