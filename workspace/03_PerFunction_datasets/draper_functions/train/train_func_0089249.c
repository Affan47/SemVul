ABValueFromString(const QString &str, const QString &currency)
{
	Q_ASSERT(abt_conv::gwen_abvlist);

	if (str.isEmpty()) {
		return NULL;
	}

	std::string s = str.toStdString();
	AB_VALUE *val;
	val = AB_Value_fromString(s.c_str());
	QString cur = currency.toUtf8();
	std::string c = cur.toStdString();
	AB_Value_SetCurrency(val, c.c_str());

	abt_conv::gwen_abvlist->append(val);
	return val;
}
