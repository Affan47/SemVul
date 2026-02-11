find(bool backwards)
{
	QString text = m_find_string->text();
	if (text.isEmpty()) {
		return;
	}
	QRegExp regex(text, !m_ignore_case->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive, QRegExp::RegExp2);

	QTextDocument::FindFlags flags;
	if (!m_ignore_case->isChecked()) {
		flags |= QTextDocument::FindCaseSensitively;
	}
	if (m_whole_words->isChecked() && !m_regular_expressions->isChecked()) {
		flags |= QTextDocument::FindWholeWords;
	}
	if (backwards) {
		flags |= QTextDocument::FindBackward;
	}

	QTextEdit* document = m_documents->currentDocument()->text();
	QTextCursor cursor = document->textCursor();
	if (!m_regular_expressions->isChecked()) {
		cursor = document->document()->find(text, cursor, flags);
	} else {
		cursor = document->document()->find(regex, cursor, flags);
	}
	if (cursor.isNull()) {
		cursor = document->textCursor();
		cursor.movePosition(!backwards ? QTextCursor::Start : QTextCursor::End);
		if (!m_regular_expressions->isChecked()) {
			cursor = document->document()->find(text, cursor, flags);
		} else {
			cursor = document->document()->find(regex, cursor, flags);
		}
	}

	if (!cursor.isNull()) {
		document->setTextCursor(cursor);
	} else {
		QMessageBox::information(this, tr("Sorry"), tr("Phrase not found."));
	}
}
