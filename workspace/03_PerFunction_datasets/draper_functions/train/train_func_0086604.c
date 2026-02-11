setNumberPiles( int p )
{
    m_number_piles = p;


    W = new card_t*[m_number_piles];
    for ( int i = 0; i < m_number_piles; ++i )
    {
        W[i] = new card_t[84];
        memset( W[i], 0, sizeof( card_t ) * 84 );
    }
    Wp = new card_t*[m_number_piles];

    Wlen = new int[m_number_piles];

    Whash = new quint32[m_number_piles];
    Wpilenum = new int[m_number_piles];
    memset( Wpilenum, 0, sizeof( int ) * m_number_piles );
}
