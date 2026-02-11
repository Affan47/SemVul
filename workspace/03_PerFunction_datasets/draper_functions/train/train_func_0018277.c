make_move(MOVE *m)
{
#if PRINT
    kDebug() << "\n\nmake_move\n";
    if ( m->totype == O_Type )
        fprintf( stderr, "move %d from %d out (at %d) Prio: %d\n\n", m->card_index, m->from, m->turn_index, m->pri );
    else
        fprintf( stderr, "move %d from %d to %d (%d) Prio: %d\n\n", m->card_index, m->from, m->to, m->turn_index, m->pri );
    print_layout();
#else

#endif

    int from, to;


    from = m->from;
    to = m->to;

    if ( m->from == deck )
    {
        for ( int i = 0; i < 8; ++i )
        {
            card_t card = *Wp[from];
            card = ( SUIT( card ) << 4 ) + RANK( card );
            ++Wp[i];
            *Wp[i] = card;
            --Wp[from];
            Wlen[i]++;
            hashpile( i );
            Wlen[from]--;
        }
        hashpile( from );
#if PRINT
        print_layout();
#endif
        return;
    }

    card_t card = NONE;
    for ( int l = m->card_index; l >= 0; --l )
    {
        card = W[from][Wlen[from]-l-1];
        Wp[from]--;
        if ( m->totype != O_Type )
        {
            Wp[to]++;
            *Wp[to] = card;
            Wlen[to]++;
        }
    }
    Wlen[from] -= m->card_index + 1;

    if ( m->turn_index == 0 )
    {
        if ( DOWN( card ) )
            card = ( SUIT( card ) << 4 ) + RANK( card );
        else
            card += ( 1 << 7 );
        W[to][Wlen[to]-m->card_index-1] = card;
    } else if ( m->turn_index != -1 )
    {
        card_t card2 = *Wp[from];
        if ( DOWN( card2 ) )
            card2 = ( SUIT( card2 ) << 4 ) + RANK( card2 );
        *Wp[from] = card2;
    }

    hashpile(from);


    if (m->totype == O_Type) {
        if ( Wlen[to] )
            *Wp[to] = card;
        else {
            Wp[to]++;
            Wlen[to]++;
            *Wp[to] = card;
        }
        Q_ASSERT( m->card_index == 0 );
    }
    hashpile(to);

#if PRINT
    print_layout();
#endif
}
