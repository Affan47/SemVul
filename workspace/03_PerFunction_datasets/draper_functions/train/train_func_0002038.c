restart( const QList<KCard*> & cards )
{
    foreach ( KCard * c, cards )
    {
        c->setPos( talon->pos() );
        c->setFaceUp( false );
        talon->add( c );
    }

    for ( int r = 0; r < 4; r++ )
    {
        for ( int c = 0; c < 8; ++c )
        {
            KCard * card = talon->topCard();
            card->setFaceUp( true );


            addCardForDeal( stack[r][c], card, true, talon->pos() );


            card->setZValue( card->zValue() + ((4 - r) * (4 - r)) + ((8 - c) * (8 - c)) );
        }
    }

    startDealAnimation();
    emit newCardsPossible(true);
}
