saveStringToFile(const QString &toSave, const QString &dirPath, const QString &filters, QWidget *parent)
{
    QWidget *wgt = parent;
    if (!parent) {
        wgt = qApp->activeWindow();
    }
    QString fileName = QFileDialog::getSaveFileName(wgt, QCoreApplication::translate("Utils", "Save to file"),
                                                    dirPath,
                                                    filters);
    if (fileName.isEmpty())
        return false;
    return Utils::saveStringToFile(toSave, fileName, Overwrite, WarnUser, wgt);
}
