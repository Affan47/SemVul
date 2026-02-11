validate (QString & input, int &) const
{
	if (input.length() > 4 ||
		input.toStdString().find_first_not_of("0123456789ABCDEFabcdef") != std::string::npos)
		return QValidator::Invalid;
	else
		return QValidator::Acceptable;
}
