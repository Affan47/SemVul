loadDocument(const QString &file)
{
    Poppler::Document *newdoc = Poppler::Document::load(file);
    if (!newdoc) {
        QMessageBox msgbox(QMessageBox::Critical, tr("Open Error"), tr("Cannot open:\n") + file,
                           QMessageBox::Ok, this);
        msgbox.exec();
        return;
    }

    while (newdoc->isLocked()) {
        bool ok = true;
        QString password = QInputDialog::getText(this, tr("Document Password"),
                                                 tr("Please insert the password of the document:"),
                                                 QLineEdit::Password, QString(), &ok);
        if (!ok) {
            delete newdoc;
            return;
        }
        newdoc->unlock(password.toLatin1(), password.toLatin1());
    }

    closeDocument();

    m_doc = newdoc;

    m_doc->setRenderHint(Poppler::Document::TextAntialiasing, m_settingsTextAAAct->isChecked());
    m_doc->setRenderHint(Poppler::Document::Antialiasing, m_settingsGfxAAAct->isChecked());
    m_doc->setRenderBackend((Poppler::Document::RenderBackend)m_settingsRenderBackendGrp->checkedAction()->data().toInt());

    Q_FOREACH(DocumentObserver *obs, m_observers) {
        obs->documentLoaded();
        obs->pageChanged(0);
    }

    m_fileSaveCopyAct->setEnabled(true);
}
