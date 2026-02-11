validate(QString &text, int &pos) const
	{
		if(isCode())
			return QValidator::Acceptable;

		return QDateTimeEdit::validate(text, pos);
	}
