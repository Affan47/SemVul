changeConnector() {
    bool ok;
    int senderIndex = sender()->property("index").toInt(&ok);
    if (!ok) return;

    ConnectorMetadata cmd;
    if (!PEUtils::fillInMetadata(senderIndex, m_scrollFrame, cmd)) return;

    emit connectorMetadataChanged(&cmd);
}
