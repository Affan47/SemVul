onActionDeleteTriggered()
{
	if (this->treeWidget->selectedItems().size() == 0) return;

	int idx = this->treeWidget->selectedItems().at(0)->data(0, Qt::UserRole).toInt();
	emit this->deleteDatedTransfer(this->m_account,
				       this->m_DatedTransfers->at(idx));
}
