createTraceMenus()
{
	m_pcbTraceMenu = menuBar()->addMenu(tr("&Routing"));
	m_pcbTraceMenu->addAction(m_newAutorouteAct);
	m_pcbTraceMenu->addAction(m_newDesignRulesCheckAct);
	m_pcbTraceMenu->addAction(m_autorouterSettingsAct);
	m_pcbTraceMenu->addAction(m_fabQuoteAct);

	QMenu * groundFillMenu = m_pcbTraceMenu->addMenu(tr("Ground Fill"));

	groundFillMenu->addAction(m_copperFillAct);
	groundFillMenu->addAction(m_groundFillAct);
	groundFillMenu->addAction(m_removeGroundFillAct);
	groundFillMenu->addAction(m_setGroundFillSeedsAct);
	groundFillMenu->addAction(m_clearGroundFillSeedsAct);
	groundFillMenu->addAction(m_setGroundFillKeepoutAct);

	m_pcbTraceMenu->addSeparator();

	m_pcbTraceMenu->addAction(m_viewFromBelowToggleAct);
	m_pcbTraceMenu->addAction(m_activeLayerBothAct);
	m_pcbTraceMenu->addAction(m_activeLayerBottomAct);
	m_pcbTraceMenu->addAction(m_activeLayerTopAct);
	m_pcbTraceMenu->addSeparator();

	m_pcbTraceMenu->addAction(m_changeTraceLayerAct);
	m_pcbTraceMenu->addAction(m_excludeFromAutorouteAct);
	m_pcbTraceMenu->addSeparator();

	m_pcbTraceMenu->addAction(m_showUnroutedAct);
	m_pcbTraceMenu->addAction(m_selectAllTracesAct);
	m_pcbTraceMenu->addAction(m_selectAllExcludedTracesAct);
	m_pcbTraceMenu->addAction(m_selectAllIncludedTracesAct);
	m_pcbTraceMenu->addAction(m_selectAllJumperItemsAct);
	m_pcbTraceMenu->addAction(m_selectAllViasAct);
	m_pcbTraceMenu->addAction(m_selectAllCopperFillAct);


    m_schematicTraceMenu = menuBar()->addMenu(tr("&Routing"));
	m_schematicTraceMenu->addAction(m_newAutorouteAct);
	m_schematicTraceMenu->addAction(m_excludeFromAutorouteAct);
	m_schematicTraceMenu->addAction(m_showUnroutedAct);
	m_schematicTraceMenu->addAction(m_selectAllTracesAct);
	m_schematicTraceMenu->addAction(m_selectAllExcludedTracesAct);
	m_schematicTraceMenu->addAction(m_selectAllIncludedTracesAct);


#ifndef QT_NO_DEBUG
	m_schematicTraceMenu->addAction(m_tidyWiresAct);
#endif

	m_breadboardTraceMenu = menuBar()->addMenu(tr("&Routing"));
	m_breadboardTraceMenu->addAction(m_showUnroutedAct);
	m_breadboardTraceMenu->addAction(m_selectAllWiresAct);

	updateTraceMenu();
	connect(m_pcbTraceMenu, SIGNAL(aboutToShow()), this, SLOT(updateTraceMenu()));
	connect(m_schematicTraceMenu, SIGNAL(aboutToShow()), this, SLOT(updateTraceMenu()));
	connect(m_breadboardTraceMenu, SIGNAL(aboutToShow()), this, SLOT(updateTraceMenu()));

    menuBar()->addSeparator();
}
