updatePileLayout( KCardPile * pile, int duration )
{
    d->sendCardsToPile( pile, QList<KCard*>(), duration, false, false );
}
