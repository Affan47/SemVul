ReadAtom (
    TypSymbolSet        follow,
    Char                mode )
{

    if ( Symbol == S_IDENT ) {
        ReadCallVarAss( follow, mode );
    }


    else if ( Symbol == S_ISBOUND ) {
        ReadIsBound( follow );
    }

    else if (IS_IN(Symbol,S_INT|S_TRUE|S_FALSE|S_CHAR|S_STRING|S_LBRACK|
                          S_REC|S_FUNCTION| S_FLOAT | S_DOT))
    {
        ReadLiteral( follow );
    }


    else if ( Symbol == S_LPAREN ) {
        Match( S_LPAREN, "(", follow );
        if ( Symbol == S_RPAREN ) {
            Match( S_RPAREN, ")", follow );
            if ( ! READ_ERROR() ) { IntrPerm( 0UL ); }
            return;
        }
        ReadExpr( S_RPAREN|follow, 'r' );
        if ( Symbol == S_COMMA ) {
            ReadPerm( follow );
            return;
        }
        Match( S_RPAREN, ")", follow );
    }


    else {
        Match( S_INT, "expression", follow );
    }
}
