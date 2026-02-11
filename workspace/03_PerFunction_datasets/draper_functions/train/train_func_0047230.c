slotFetched()
{

    const MetaXml::Reader_1 * reader = m_connector->reader();
    if (!reader || reader->releases.isEmpty()) {
        slotError(tr("XML Error"));
        return;
    }
    ui->progressBar->hide();


    m_release = reader->releases.first();
    ui->nextVersion->setText(tr("%1 (%2)").arg(m_release.version).arg(m_release.name));


    if (m_release.version.compare(QCoreApplication::applicationVersion(), Qt::CaseInsensitive)) {
        QPushButton * dlButton = ui->buttonBox->addButton(tr("Download"), QDialogButtonBox::NoRole);
        connect(dlButton, SIGNAL(clicked()), this, SLOT(slotDownload()));
    }
}
