filter() const
{

	QRegExp::PatternSyntax type;
	if (stringButton_->isChecked())
		type = QRegExp::FixedString;
	else if (regExpButton_->isChecked())
		type = QRegExp::RegExp;
	else if (simpRegExpButton_->isChecked())
		type = QRegExp::Wildcard;


	Qt::CaseSensitivity cs = caseSensitiveCheck_->isChecked()
	                         ? Qt::CaseSensitive :  Qt::CaseInsensitive;


	return QRegExp(patternEdit_->text(), cs, type);
}
