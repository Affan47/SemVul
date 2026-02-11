ReadLiteral (
    TypSymbolSet        follow )
{

    if ( Symbol == S_INT ) {
        if ( ! READ_ERROR() ) { IntrIntExpr( Value ); }
        Match( S_INT, "integer", follow );
    }


    else if ( Symbol == S_FLOAT ) {
        if ( ! READ_ERROR() ) { IntrFloatExpr( Value ); }
        Match( S_FLOAT, "float", follow );
    }


    else if ( Symbol == S_PARTIALINT || Symbol == S_PARTIALFLOAT1 ||
	      Symbol == S_PARTIALFLOAT2 ) {
         ReadLongNumber( follow );
    }


    else if ( Symbol == S_TRUE ) {
        Match( S_TRUE, "true", follow );
        IntrTrueExpr();
    }


    else if ( Symbol == S_FALSE ) {
        Match( S_FALSE, "false", follow );
        IntrFalseExpr();
    }


    else if ( Symbol == S_CHAR ) {
        if ( ! READ_ERROR() ) { IntrCharExpr( Value[0] ); }
        Match( S_CHAR, "character", follow );
    }


    else if ( Symbol == S_STRING || Symbol == S_PARTIALSTRING ) {
        ReadString( follow );
    }


    else if ( Symbol == S_LBRACK ) {
        ReadListExpr( follow );
    }


    else if ( Symbol == S_REC ) {
        ReadRecExpr( follow );
    }


    else if ( Symbol == S_FUNCTION ) {
        ReadFuncExpr( follow );
    }

    else if (Symbol == S_DOT ) {


      Symbol = S_PARTIALFLOAT1;
      Value[0] = '.';
      Value[1] = '\0';
      ReadLongNumber( follow );
    }


    else {
        Match( S_INT, "literal", follow );
    }
}
