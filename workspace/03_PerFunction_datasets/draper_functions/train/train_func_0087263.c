checkAdd(const PatPile * pile, const QList<KCard*> & oldCards, const QList<KCard*> & newCards) const
{
    switch ( pile->pileRole() )
    {
    case PatPile::Foundation:
        return newCards.size() == 1 && canMoveAway( newCards.first() );
    case PatPile::Tableau:
        return oldCards.isEmpty() && newCards.size() == 1;
    case PatPile::Stock:
    default:
        return false;
    }
}
