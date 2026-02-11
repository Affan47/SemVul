on_buttonBox_clicked(QAbstractButton* button)
{
	switch(this->ui->buttonBox->standardButton(button)) {
	case QDialogButtonBox::RestoreDefaults:
	case QDialogButtonBox::Reset:
		this->loadFromSettings();
		break;
	case QDialogButtonBox::Save:
	case QDialogButtonBox::SaveAll:
		this->saveToSettings();
		break;
	case QDialogButtonBox::Cancel:
		this->reject();
		break;
	case QDialogButtonBox::Ok:
		this->saveToSettings();
		this->accept();
		break;

	default:

		break;
	}
}
