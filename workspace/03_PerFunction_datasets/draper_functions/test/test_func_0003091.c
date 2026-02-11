dumptoken(DAPlexstate* lexstate)
{
    fprintf(stderr,"TOKEN = |%s|\n",ocbytescontents(lexstate->yytext));
}
