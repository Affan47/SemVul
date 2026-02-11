connectorMetadataChanged(ConnectorMetadata * cmd)
{
    int index;
    QDomElement connector = findConnector(cmd->connectorID, index);
    if (connector.isNull()) return;

    ConnectorMetadata oldcmd;
	fillInMetadata(connector, oldcmd);

    ChangeConnectorMetadataCommand * ccmc = new ChangeConnectorMetadataCommand(this, &oldcmd, cmd, NULL);
    ccmc->setText(tr("Change connector %1").arg(cmd->connectorName));
    bool skipFirstRedo = (sender() == m_connectorsView);
    if (skipFirstRedo) {
        ccmc->setSkipFirstRedo();
        changeConnectorElement(connector, cmd);
        initConnectors(false);
    }
    m_undoStack->waitPush(ccmc, SketchWidget::PropChangeDelay);
}
