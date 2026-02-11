openFile()
{

    QString dir;
    dir = QFileDialog::getExistingDirectory(this, tr("Choose a patient file directory"),
                                            settings()->path(Core::ISettings::CompleteFormsPath));

    if (dir.isEmpty())
        return false;
    return loadFile(dir);
}
