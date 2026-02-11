compile_sentence_end ()
{
    token_next() ;

    if (token.type == NOTOKEN)
        return 1;

    if (token.type == IDENTIFIER && token.code == identifier_semicolon)
        return 0 ;


    compile_error (MSG_EXPECTED, ";") ;
    return 0;
}
