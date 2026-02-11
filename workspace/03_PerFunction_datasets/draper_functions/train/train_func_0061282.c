comboBoxNewAccountSelected(const aqb_AccountInfo *selAcc)
{
	if (selAcc != NULL) {
		this->currAccount = selAcc;
		this->localOwner->setText(selAcc->OwnerName());
		this->localAccountNumber->setText(selAcc->Number());
		this->localBankCode->setText(selAcc->BankCode());
		this->localBankName->setText(selAcc->BankName());
		this->localIBAN->setText(selAcc->IBAN());
		this->localBIC->setText(selAcc->BIC());
	}
	emit this->accountChanged(selAcc);
}
