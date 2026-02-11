comboBoxNewAccountSelected(int idx)
{
	const aqb_AccountInfo* newSelAcc;
	newSelAcc = this->comboBox->itemData(idx, Qt::UserRole).value<const aqb_AccountInfo*>();
	emit this->selectedAccountChanged(newSelAcc);
}
