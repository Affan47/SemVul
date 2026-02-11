hideShowTraceMenu() {
    if (m_pcbTraceMenu) m_pcbTraceMenu->menuAction()->setVisible(m_currentGraphicsView == m_pcbGraphicsView);
	if (m_schematicTraceMenu) m_schematicTraceMenu->menuAction()->setVisible(m_currentGraphicsView == m_schematicGraphicsView);
	if (m_breadboardTraceMenu) m_breadboardTraceMenu->menuAction()->setVisible(m_currentGraphicsView == m_breadboardGraphicsView);
}
