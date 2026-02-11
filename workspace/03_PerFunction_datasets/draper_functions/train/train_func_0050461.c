showSettingsDialog()
{
	QDialog* settingsDialog = new QDialog(this);
	m_ui = new Ui_settingsDialog();
	m_ui->setupUi(settingsDialog);
	m_ui->antialiasCheckBox->setCheckState(m_antialias ? Qt::Checked : Qt::Unchecked);
	m_ui->roundedCheckBox->setCheckState(m_rounded ? Qt::Checked : Qt::Unchecked);
	m_ui->replotOnResizeCheckBox->setCheckState(m_replotOnResize ? Qt::Checked : Qt::Unchecked);
	QPixmap samplePixmap(m_ui->sampleColorLabel->size());
	samplePixmap.fill(m_backgroundColor);
	m_ui->sampleColorLabel->setPixmap(samplePixmap);
	m_chosenBackgroundColor = m_backgroundColor;
	connect(m_ui->backgroundButton, SIGNAL(clicked()), this, SLOT(settingsSelectBackgroundColor()));
	settingsDialog->exec();

	if (settingsDialog->result() == QDialog::Accepted)
	{
		m_backgroundColor = m_chosenBackgroundColor;
		m_antialias = (m_ui->antialiasCheckBox->checkState() == Qt::Checked);
		m_rounded = (m_ui->roundedCheckBox->checkState() == Qt::Checked);
		m_replotOnResize = (m_ui->replotOnResizeCheckBox->checkState() == Qt::Checked);
		applySettings();
		saveSettings();
	}
}
