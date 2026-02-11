setPlayer(MediaPlayer* player)
{
    if (m_player == player) return;
    if (m_player) m_player->deleteLater();
    m_player = player;
    connect(player->mediaObject(), SIGNAL(metaDataChanged()), SLOT(slotMetaDataChanged()));
    player->setParent(widget());
    widget()->layout()->addWidget(player);
}
