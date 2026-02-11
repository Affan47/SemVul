addFile(QString & file)
{
    outDebug(5, std::cout << "pickupFile:" << file.toStdString() << std::endl);
    QStandardItem *parentItem = mModel->invisibleRootItem();
    parentItem->appendRow(new QStandardItem(file));
    ui.sockdevCheckBox->setEnabled (mModel->rowCount() == 0);
}
