setDeckContents( int copies, const QList<KCardDeck::Suit> & suits )
{
    Q_ASSERT( copies >= 1 );
    Q_ASSERT( !suits.isEmpty() );


    QList<quint32> ids;
    unsigned int number = 0;
    for ( int i = 0; i < copies; ++i )
        foreach ( const KCardDeck::Rank & r, KCardDeck::standardRanks() )
            foreach ( const KCardDeck::Suit & s, suits )
                ids << KCardDeck::getId( s, r, number++ );

    deck()->setDeckContents( ids );
}
