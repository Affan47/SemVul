openFile(const QString &file)
{
    if (d->m_CollectionModel->rowCount() > 0) {
        int r = Utils::withButtonsMessageBox(
                tr("Opening an ICD collection: merge or replace?"),
                tr("There is an ICD collection inside the editor, "
                   "do you to replace it or to add the opened collection?"),
                QString(), QStringList() << tr("Replace collection") << tr("Add to collection"),
                tr("Open a collection") + " - " + qApp->applicationName());
        if (r == 0) {
            IcdIO io;
            io.icdCollectionFromXml(d->m_CollectionModel, Utils::readTextFile(file, Utils::DontWarnUser));
        } else if (r==1) {
            IcdIO io;
            io.icdCollectionFromXml(d->m_CollectionModel, Utils::readTextFile(file, Utils::DontWarnUser), ICD::IcdIO::AddToModel);
        }
    } else {
        IcdIO io;
        io.icdCollectionFromXml(d->m_CollectionModel, Utils::readTextFile(file, Utils::DontWarnUser));
    }
    ui->collectionView->hideColumn(ICD::IcdCollectionModel::CodeWithoutDaget);
    ui->collectionView->hideColumn(ICD::IcdCollectionModel::HumanReadableDaget);
    ui->collectionView->hideColumn(ICD::IcdCollectionModel::SID);
    ui->collectionView->hideColumn(ICD::IcdCollectionModel::DagCode);
    ui->collectionView->expandAll();
}
