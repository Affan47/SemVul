updatePixmap()
{
    QList<QGraphicsItem*> children = childItems();
    qDeleteAll(children);

    QList<QString> spriteKeys = s_stateNames[m_state];
    setSpriteKey(spriteKeys[0]);
    for(int i=1; i<spriteKeys.count(); i++)
        addOverlay(spriteKeys[i]);
    if(m_state == KMinesState::Revealed)
    {
        if(m_digit != 0)
            addOverlay(s_digitNames[m_digit]);
        else if(m_hasMine)
        {
            if(m_exploded)
                addOverlay(QLatin1String( "explosion" ));
            addOverlay(QLatin1String( "mine" ));
        }
    }
}
