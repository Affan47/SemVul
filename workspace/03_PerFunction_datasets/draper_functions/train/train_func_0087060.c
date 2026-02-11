gifti_valid_nbyper(int nbyper, int whine)
{
    int c;


    for( c = sizeof(gifti_type_list) / sizeof(gifti_type_ele) - 1; c > 0; c-- )
        if( nbyper == gifti_type_list[c].nbyper ) return 1;

    if( whine || G.verb > 3 )
        fprintf(stderr,"** invalid nbyper value %d\n", nbyper);

    return 0;
}
