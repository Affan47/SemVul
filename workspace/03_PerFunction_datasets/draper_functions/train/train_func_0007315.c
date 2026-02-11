findConnectorItem()
{
    if (m_currentGraphicsView == NULL) return NULL;

    QDomElement connector = m_connectorList.at(m_peToolView->currentConnectorIndex());
    if (connector.isNull()) return NULL;

	QString svgID, terminalID;
    bool ok = ViewLayer::getConnectorSvgIDs(connector, m_currentGraphicsView->viewID(), svgID, terminalID);
    if (!ok) return NULL;

    QList<PEGraphicsItem *> pegiList = getPegiList(m_currentGraphicsView);
    foreach (PEGraphicsItem * pegi, pegiList) {
        if (pegi->element().attribute("id") == svgID) return pegi;
    }

    return NULL;
}
