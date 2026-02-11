ReadAri (
    TypSymbolSet        follow,
    Char                mode )
{
    UInt                symbol;


    ReadTerm( follow, mode );


    while ( IS_IN( Symbol, S_PLUS|S_MINUS ) ) {
        symbol = Symbol;
        Match( Symbol, "+ or -", follow );
        ReadTerm( follow, 'r' );
        if ( ! READ_ERROR() ) {
            if      ( symbol == S_PLUS  ) { IntrSum();  }
            else if ( symbol == S_MINUS ) { IntrDiff(); }
        }
    }
}
