translateMove( const MOVE & m )
{
    if ( m.from == deck )
        return MoveHint();

    PatPile *frompile = deal->stack[m.from / 8][m.from % 8];
    KCard *card = frompile->topCard();

    if ( m.to == aces )
    {
        return MoveHint( card, deal->aces, m.pri );
    } else {
        return MoveHint( card, deal->stack[m.to / 8][m.to % 8], m.pri );
    }
}
