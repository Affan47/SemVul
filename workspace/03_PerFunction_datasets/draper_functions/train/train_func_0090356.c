displaySelectionClicked()
{
    QList<QSslCertificate> certs;
    foreach(const QTreeWidgetItem *twItem, m_ui.treeWidget->selectedItems()) {
        const CaCertificateItem *item = dynamic_cast<const CaCertificateItem *>(twItem);
        Q_ASSERT(item);
        if (item) {
            certs += item->m_cert;
        }
    }
    DisplayCertDialog dc(this);
    dc.setCertificates(certs);
    dc.exec();
}
