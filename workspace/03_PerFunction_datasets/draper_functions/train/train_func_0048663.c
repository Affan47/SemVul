new_()
{
    if (inputText->document()->isModified() &&
        QMessageBox::question(this,
            tr("Alt_Key - Unsaved Changes"),
            tr("Save unsaved changes?"),
            QMessageBox::Yes|QMessageBox::No) == QMessageBox::Yes)
        save();
    inputText->clear();
    inputText->document()->setModified(false);
    outputText->clear();
    logText->clear();
    filename.clear();
    inputText->setFocus();
    setWindowTitle(tr("Alt_Key - Unnamed"));
}
