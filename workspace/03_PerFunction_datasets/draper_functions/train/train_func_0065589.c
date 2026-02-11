mousePressEvent( QGraphicsSceneMouseEvent * e )
{
    if ( isKeyboardModeActive() )
        setKeyboardModeActive( false );

    QGraphicsItem * item = itemAt( e->scenePos() );
    KCard * card = qgraphicsitem_cast<KCard*>( item );
    KCardPile * pile = qgraphicsitem_cast<KCardPile*>( item );

    if ( e->button() == Qt::LeftButton && ( card || pile ) )
    {
        e->accept();

        if ( card
             && !isCardAnimationRunning()
             && !d->cardsBeingDragged.contains( card ) )
        {
            QList<KCard*> cards = card->pile()->topCardsDownTo( card );

            if ( allowedToRemove( card->pile(), cards.first() ) )
            {
                d->cardsBeingDragged = cards;
                foreach ( KCard * c, d->cardsBeingDragged )
                {
                    c->stopAnimation();
                    c->raise();
                }
            }

            d->dragStarted = false;
            d->startOfDrag = e->scenePos();
        }
    }
    else
    {
        QGraphicsScene::mousePressEvent( e );
    }
}
