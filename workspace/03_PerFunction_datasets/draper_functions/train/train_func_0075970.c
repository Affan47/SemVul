saveRaw(bool checked)
{
	if (!checked) {
		if (m_saveRaw.openMode())
			m_saveRaw.close();
		return;
	}

	SaveDialog *dlg = new SaveDialog(this, "Save Raw Frames");
	dlg->setAttribute(Qt::WA_DeleteOnClose);
	dlg->setFileMode(QFileDialog::AnyFile);
	dlg->setAcceptMode(QFileDialog::AcceptSave);
	dlg->setModal(false);
	connect(dlg, SIGNAL(fileSelected(const QString &)), this, SLOT(openRawFile(const QString &)));
	connect(dlg, SIGNAL(rejected()), this, SLOT(rejectedRawFile()));
	dlg->show();
}
