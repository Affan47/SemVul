checkWidgets() const
{
	if (!InsetParamsWidget::checkWidgets())
		return false;
	QString const description = descriptionTE->toPlainText();
	return !symbolED->text().isEmpty() && !description.isEmpty();
}

}
