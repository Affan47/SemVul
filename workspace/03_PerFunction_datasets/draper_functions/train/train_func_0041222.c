undo_move(MOVE *m)
{
#if PRINT
    if ( m->totype == O_Type )
        fprintf( stderr, "\nundo move %d from %d out (at %d)\n\n", m->card_index, m->from, m->turn_index );
    else
        fprintf( stderr, "\nundo move %d from %d to %d (%d)\n\n", m->card_index, m->from, m->to, m->turn_index );
    print_layout();

#endif

    int from = m->from;
    int to = m->to;

    Q_ASSERT( to == 7 );
    Q_ASSERT( from != 7 );


    if ( from == 8 && to == 7 )
    {
        card_t card = *Wp[7];
        Wp[7]--;
        Wlen[7]--;
        card = ( SUIT( card ) << 4 ) + RANK( card ) + ( 1 << 7 );
        Wp[8]++;
        *Wp[8] = card;
        Wlen[8]++;
        hashpile( 7 );
        hashpile( 8 );
#if PRINT
        print_layout();
#endif
        return;
    }

    card_t card = *Wp[to];
    Wp[to]--;
    Wlen[to]--;

    Wp[from]++;
    *Wp[from] = card;
    Wlen[from]++;

    hashpile(from);
    hashpile(to);
#if PRINT
    print_layout();
#endif
}
