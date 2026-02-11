deleteRide()
{
    QTreeWidgetItem *_item = treeWidget->currentItem();
    if (_item==NULL || _item->type() != RIDE_TYPE) {
        QMessageBox::critical(this, tr("Delete Activity"), tr("No activity selected!"));
        return;
    }
    RideItem *item = static_cast<RideItem*>(_item);
    QMessageBox msgBox;
    msgBox.setText(tr("Are you sure you want to delete the activity:"));
    msgBox.setInformativeText(item->fileName);
    QPushButton *deleteButton = msgBox.addButton(tr("Delete"),QMessageBox::YesRole);
    msgBox.setStandardButtons(QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.exec();
    if(msgBox.clickedButton() == deleteButton)
        removeCurrentRide();
}
