checkAccount(const QString &country, const QString &branchId,
			       const QString &bankId, const QString &accountId,
			       QString &result) const
{
	AB_BANKINFO_CHECKRESULT res;
	res = AB_Banking_CheckAccount(this->ab,
				      country.toUtf8(), branchId.toUtf8(),
				      bankId.toUtf8(), accountId.toUtf8());
	switch (res) {
	case AB_BankInfoCheckResult_Ok:
		result = QObject::tr("OK");
		return true;
		break;
	case AB_BankInfoCheckResult_NotOk:
		result = QObject::tr("Nicht OK");
		break;
	case AB_BankInfoCheckResult_UnknownBank:
		result = QObject::tr("Bank unbekannt");
		break;
	case AB_BankInfoCheckResult_UnknownResult:
		result = QObject::tr("Ergebniss unbekannt");
		break;
	default:
		result = QObject::tr("Unbekannter Ergebnisstyp");
		break;
	}

	return false;
}
