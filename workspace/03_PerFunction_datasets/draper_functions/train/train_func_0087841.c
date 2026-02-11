createAst()
{
    for (Token *tok = _front; tok; tok = tok ? tok->next() : NULL) {
        tok = createAstAtToken(tok, isCPP());
    }
}
