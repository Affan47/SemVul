moveCardsToPileAtSpeed( const QList<KCard*> & cards, KCardPile * pile, qreal velocity )
{
    if ( cards.isEmpty() )
        return;

    KCardPile * source = cards.first()->pile();
    d->sendCardsToPile( pile, cards, velocity, true, false );
    if ( source )
        d->sendCardsToPile( source, QList<KCard*>(), cardMoveDuration, false, false );
    cardsMoved( cards, source, pile );
}
