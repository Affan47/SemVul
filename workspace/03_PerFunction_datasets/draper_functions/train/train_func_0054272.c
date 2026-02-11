closeEditor(QWidget* editor, QAbstractItemDelegate::EndEditHint hint)
{
	Q_UNUSED(editor);

	if (hint == QAbstractItemDelegate::SubmitModelCache) {
		QList<QLineEdit*> lineEdits;
		lineEdits << ui_.host << ui_.room << ui_.nickname;
		foreach(QLineEdit* lineEdit, lineEdits) {
			if (lineEdit->text().isEmpty()) {
				lineEdit->setFocus();
				break;
			}
		}
	}
}
