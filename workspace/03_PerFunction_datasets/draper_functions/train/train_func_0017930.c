ReadContinue (
    TypSymbolSet        follow )
{

    Match( S_CONTINUE, "continue", follow );


    if ( ! READ_ERROR() ) { IntrContinue(); }
}
