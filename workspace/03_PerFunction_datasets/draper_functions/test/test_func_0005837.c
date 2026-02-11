createActiveLayerActions() {

	m_viewFromBelowToggleAct = new QAction(tr("View from below"), this);
	m_viewFromBelowToggleAct->setStatusTip(tr("View the PCB from the bottom layers upwards"));
    m_viewFromBelowToggleAct->setCheckable(true);
    m_viewFromBelowToggleAct->setChecked(false);
	connect(m_viewFromBelowToggleAct, SIGNAL(triggered()), this, SLOT(setViewFromBelowToggle()));

	m_viewFromBelowAct = new QAction(tr("View from below"), this);
	m_viewFromBelowAct->setStatusTip(tr("View the PCB from the bottom layers upwards"));
	connect(m_viewFromBelowAct, SIGNAL(triggered()), this, SLOT(setViewFromBelow()));

	m_viewFromAboveAct = new QAction(tr("View from above"), this);
	m_viewFromAboveAct->setStatusTip(tr("View the PCB from the top layers downwards"));
	connect(m_viewFromAboveAct, SIGNAL(triggered()), this, SLOT(setViewFromAbove()));

	m_activeLayerBothAct = new QAction(tr("Set both copper layers clickable"), this);
	m_activeLayerBothAct->setStatusTip(tr("Set both copper layers clickable"));
	m_activeLayerBothAct->setShortcut(tr("Shift+Ctrl+3"));
	connect(m_activeLayerBothAct, SIGNAL(triggered()), this, SLOT(activeLayerBoth()));

	m_activeLayerTopAct = new QAction(tr("Set copper top layer clickable"), this);
	m_activeLayerTopAct->setStatusTip(tr("Set copper top layer clickable"));
	m_activeLayerTopAct->setShortcut(tr("Shift+Ctrl+2"));
	connect(m_activeLayerTopAct, SIGNAL(triggered()), this, SLOT(activeLayerTop()));

	m_activeLayerBottomAct = new QAction(tr("Set copper bottom layer clickable"), this);
	m_activeLayerBottomAct->setStatusTip(tr("Set copper bottom layer clickable"));
	m_activeLayerBottomAct->setShortcut(tr("Shift+Ctrl+1"));
	connect(m_activeLayerBottomAct, SIGNAL(triggered()), this, SLOT(activeLayerBottom()));
}
