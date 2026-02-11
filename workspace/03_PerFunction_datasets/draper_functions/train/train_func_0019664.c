make_move(MOVE *m)
{
#if PRINT
    if ( m->totype == O_Type )
        fprintf( stderr, "\nmake move %d from %d out %d (at %d)\n\n", m->card_index, m->from, m->to, m->turn_index );
    else
        fprintf( stderr, "\nmake move %d from %d to %d (%d)\n\n", m->card_index, m->from, m->to, m->turn_index );
    print_layout();
#else

#endif

    int from, to;
    from = m->from;
    to = m->to;

    card_t card = *Wp[from];
    Wlen[from]--;
    Wp[from]--;

    hashpile(from);


    if (m->totype == O_Type) {
        if ( RANK( W[8][to] ) == PS_KING )
            W[8][to] = W[8][to] - PS_KING + PS_ACE;
        else
            W[8][to]++;
        Q_ASSERT( m->card_index == 0 );
        hashpile( 8 );
    } else {
        Wp[to]++;
        *Wp[to] = card;
        Wlen[to]++;
        hashpile( to );
    }

#if PRINT
    print_layout();
#endif
}
