createAutosaveForm() {
	QGroupBox * autosave = new QGroupBox(tr("Autosave"), this );

	QHBoxLayout * zhlayout = new QHBoxLayout();
	zhlayout->setSpacing(SPACING);

	QCheckBox * box = new QCheckBox(tr("Autosave every:"));
	box->setChecked(MainWindow::AutosaveEnabled);
	zhlayout->addWidget(box);

	zhlayout->addSpacerItem(new QSpacerItem(0,0,QSizePolicy::Expanding));

	QSpinBox * spinBox = new QSpinBox;
	spinBox->setMinimum(1);
	spinBox->setMaximum(60);
	spinBox->setValue(MainWindow::AutosaveTimeoutMinutes);
	spinBox->setMaximumWidth(80);
	zhlayout->addWidget(spinBox);

	QLabel * label = new QLabel(tr("minutes"));
	zhlayout->addWidget(label);

	autosave->setLayout(zhlayout);

	connect(box, SIGNAL(clicked(bool)), this, SLOT(toggleAutosave(bool)));
	connect(spinBox, SIGNAL(valueChanged(int)), this, SLOT(changeAutosavePeriod(int)));


	return autosave;
}
