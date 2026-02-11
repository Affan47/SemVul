addService(const QString& xmlFilePath)
{
    QFile *f = new QFile(xmlFilePath);
    bool b = addService(f);
    delete f;
    return b;
}
