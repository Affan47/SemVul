get_el_valence( int nPeriodicNum, int charge, int val_num )
{
    if ( charge < MIN_ATOM_CHARGE || charge > MAX_ATOM_CHARGE || val_num >= MAX_NUM_VALENCES )
        return 0;
    return ElData[nPeriodicNum>1? nPeriodicNum+1:0].cValence[NEUTRAL_STATE+charge][val_num];
}
