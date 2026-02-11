GetCoffType( unsigned short StabType ){

    STABCOFFMAP *p;

    for ( p = FindFirstListObject( &ci->ListOfTypes ); p != 0; p = FindNextListObject( &ci->ListOfTypes) ) {
        if ( p->StabType == StabType )
            return( p->CoffType );
    }
    return( 0 );
}
