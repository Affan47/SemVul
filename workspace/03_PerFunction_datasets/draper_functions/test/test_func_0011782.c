mouseReleaseEvent( QGraphicsSceneMouseEvent * e )
{
    QGraphicsItem * topItem = itemAt( e->scenePos() );
    KCard * card = qgraphicsitem_cast<KCard*>( topItem );
    KCardPile * pile = qgraphicsitem_cast<KCardPile*>( topItem );

    if ( e->button() == Qt::LeftButton && !d->dragStarted && !d->cardsBeingDragged.isEmpty() )
    {
        updatePileLayout( d->cardsBeingDragged.first()->pile(), cardMoveDuration );
        d->cardsBeingDragged.clear();
    }

    if ( e->button() == Qt::LeftButton && !d->cardsBeingDragged.isEmpty() )
    {
        e->accept();

        KCardPile * destination = d->bestDestinationPileUnderCards();
        if ( destination )
            cardsDroppedOnPile( d->cardsBeingDragged, destination );
        else
            updatePileLayout( d->cardsBeingDragged.first()->pile(), cardMoveDuration );
        d->cardsBeingDragged.clear();
        d->dragStarted = false;
        clearHighlightedItems();
    }
    else if ( card && !isCardAnimationRunning() )
    {
        e->accept();
        if ( e->button() == Qt::LeftButton )
        {
            emit cardClicked( card );
            if ( card->pile() )
                emit card->pile()->clicked( card );
        }
        else if ( e->button() == Qt::RightButton )
        {
            emit cardRightClicked( card );
            if ( card->pile() )
                emit card->pile()->rightClicked( card );
        }
    }
    else if ( pile && !isCardAnimationRunning() )
    {
        e->accept();
        if ( e->button() == Qt::LeftButton )
        {
            emit pileClicked( pile );
            emit pile->clicked( 0 );
        }
        else if ( e->button() == Qt::RightButton )
        {
            emit pileRightClicked( pile );
            emit pile->rightClicked( 0 );
        }
    }
    else
    {
        QGraphicsScene::mouseReleaseEvent( e );
    }
}
