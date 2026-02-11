skipeoltok(strom)
truc *strom;
{
    ifun0 nextch;
    int tok;

    nextch = chread(strom);
    tok = cStream->tok;
    while(tok == EOLTOK) {
        nextch();
        tok = nexttok(strom,0);
    }
    return(tok);
}
