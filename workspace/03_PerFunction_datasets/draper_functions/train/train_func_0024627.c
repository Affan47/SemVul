startNewGame()
{
    if(m_animator->isAnimating())
        return;


    m_selPos = FieldPos();
    m_numFreeCells = FIELD_SIZE*FIELD_SIZE;
    m_score = 0;
    m_bonusScore = 0;
    m_placeBalls = true;
    m_gameOver = false;
    m_itemsToDelete.clear();
    m_nextColors.clear();
    m_focusItem->setPos(0, 0);
    m_focusItem->hide();

    m_popupItem->forceHide();


    QList<QGraphicsItem*> itemlist = items();
    foreach( QGraphicsItem* item, itemlist )
    {
        BallItem* ball = qgraphicsitem_cast<BallItem*>(item);
        if( ball )
        {
            removeItem(item);
            delete item;
        }
    }

    for(int x=0; x<FIELD_SIZE; ++x)
        for(int y=0; y<FIELD_SIZE; ++y)
            m_field[x][y] = 0;


    for(int i=0; i<3; i++)
    {

        BallColor c = static_cast<BallColor>(m_randomSeq.getLong(static_cast<int>(NumColors)));
        m_nextColors.append(c);
    }

    emit stateChanged(QLatin1String( "not_undoable" ));

    nextThreeBalls();
}
