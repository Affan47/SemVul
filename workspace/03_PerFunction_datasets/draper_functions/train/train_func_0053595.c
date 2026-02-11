cardsMoved( const QList<KCard*> & cards, KCardPile * oldPile, KCardPile * newPile )
{
    if ( oldPile->isEmpty() && !talon->isEmpty() )
    {
        PatPile * p = dynamic_cast<PatPile*>( oldPile );
        if ( p && p->pileRole() == PatPile::Tableau )
            flipCardToPile( talon->topCard(), oldPile, DURATION_MOVE );
    }

    DealerScene::cardsMoved( cards, oldPile, newPile );
}
