on_treeWidget_itemSelectionChanged()
{
	if (this->ui->treeWidget->selectedItems().size() > 0) {
		QTreeWidgetItem *selItem = this->ui->treeWidget->selectedItems().at(0);
		int accountID = selItem->data(0, Qt::UserRole).toInt();
		aqb_AccountInfo *acc = this->m_accounts->getAccountHash().value(accountID, NULL);
		emit this->Account_Changed(acc);
	} else {
		emit this->Account_Changed(NULL);
	}
}
