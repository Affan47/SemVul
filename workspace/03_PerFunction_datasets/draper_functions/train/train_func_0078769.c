saveStringToFile(const QString &toSave, const QString &toFile, IOMode iomode, const Warn warnUser, QWidget *parent)
{
    return saveStringToEncodedFile(toSave, toFile, "UTF-8", iomode, warnUser, parent);
}
