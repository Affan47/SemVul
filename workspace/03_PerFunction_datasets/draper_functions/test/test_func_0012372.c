createFileMenuActions() {
	MainWindow::createFileMenuActions();

	m_reuseBreadboardAct = new QAction(tr("Reuse breadboard image"), this);
	m_reuseBreadboardAct->setStatusTip(tr("Reuse the breadboard image in this view"));
	connect(m_reuseBreadboardAct, SIGNAL(triggered()), this, SLOT(reuseBreadboard()));

	m_reuseSchematicAct = new QAction(tr("Reuse schematic image"), this);
	m_reuseSchematicAct->setStatusTip(tr("Reuse the schematic image in this view"));
	connect(m_reuseSchematicAct, SIGNAL(triggered()), this, SLOT(reuseSchematic()));

	m_reusePCBAct = new QAction(tr("Reuse PCB image"), this);
	m_reusePCBAct->setStatusTip(tr("Reuse the PCB image in this view"));
	connect(m_reusePCBAct, SIGNAL(triggered()), this, SLOT(reusePCB()));
}
