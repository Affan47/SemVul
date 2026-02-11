checkPrefering(const PatPile * pile, const QList<KCard*> & oldCards, const QList<KCard*> & newCards) const
{
    return pile->pileRole() == PatPile::Tableau
           && !oldCards.isEmpty()
           && oldCards.last()->suit() == newCards.first()->suit();
}
