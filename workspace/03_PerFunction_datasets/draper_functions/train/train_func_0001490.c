updateLayout()
{
	ChatEdit* newEdit = createTextEdit();

	if (textEdit_) {


		textEdit_->setCheckSpelling(false);
		newEdit->setCheckSpelling(false);

		moveData(newEdit, textEdit_);

		newEdit->setCheckSpelling(ChatEdit::checkSpellingGloballyEnabled());
	}

	delete textEdit_;
	textEdit_ = newEdit;
	layout_->addWidget(textEdit_);
	emit textEditCreated(textEdit_);
}
