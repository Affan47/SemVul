focusInEvent(QFocusEvent *event)
	{
		if(mCompleter)
			mCompleter->setWidget(this);

		QPlainTextEdit::focusInEvent(event);
	}
