getHints()
{
    QList<MoveHint> hintList = getSolverHints();

    if ( isDemoActive() )
        return hintList;

    foreach (PatPile * store, patPiles())
    {
        if (store->isEmpty())
            continue;

        QList<KCard*> cards = store->cards();
        while (cards.count() && !cards.first()->isFaceUp())
            cards.erase(cards.begin());

        QList<KCard*>::Iterator iti = cards.begin();
        while (iti != cards.end())
        {
            if (allowedToRemove(store, (*iti)))
            {
                foreach (PatPile * dest, patPiles())
                {
                    int cardIndex = store->indexOf(*iti);
                    if (cardIndex == 0 && dest->isEmpty() && !dest->isFoundation())
                        continue;

                    if (!checkAdd(dest, dest->cards(), cards))
                        continue;

                    if ( dest->isFoundation() )
                        continue;

                    QList<KCard*> cardsBelow = cards.mid(0, cardIndex);

                    if ((cardsBelow.isEmpty() && !dest->isEmpty()) || !checkAdd(store, cardsBelow, cards))
                    {
                        hintList << MoveHint( *iti, dest, 0 );
                    }
                    else if (checkPrefering( dest, dest->cards(), cards )
                             && !checkPrefering( store, cardsBelow, cards ))
                    {
                        hintList << MoveHint( *iti, dest, 0 );
                    }
                }
            }
            cards.erase(iti);
            iti = cards.begin();
        }
    }
    return hintList;
}
