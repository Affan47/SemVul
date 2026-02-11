syntaxCopy(Dsymbol *s)
{
    StructDeclaration *sd;

    if (s)
        sd = (StructDeclaration *)s;
    else
        sd = new StructDeclaration(loc, ident);
    ScopeDsymbol::syntaxCopy(sd);
    return sd;
}
