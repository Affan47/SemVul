createAndSendModifyDatedTransfer(const widgetTransfer *sender)
{
	const aqb_AccountInfo *acc = sender->localAccount->getAccount();
	const abt_transaction *origT = sender->getOriginalTransaction();


	abt_transaction *newT = new abt_transaction(*origT);

	newT->fillLocalFromAccount(acc->get_AB_ACCOUNT());


	newT->setIdForApplication(QDateTime::currentDateTime().toTime_t());

	newT->setRemoteAccountNumber(sender->remoteAccount->getAccountNumber());
	newT->setRemoteName(QStringList(sender->remoteAccount->getName()));
	newT->setRemoteBankCode(sender->remoteAccount->getBankCode());
	newT->setRemoteBankName(sender->remoteAccount->getBankName());

	newT->setValue(sender->value->getValueABV());

	newT->setPurpose(sender->purpose->getPurpose());

	newT->setTextKey(sender->textKey->getTextKey());

	newT->setDate(sender->datedDate->getDate());

	this->jobctrl->addModifyDatedTransfer(acc, newT);

	delete newT;
}
