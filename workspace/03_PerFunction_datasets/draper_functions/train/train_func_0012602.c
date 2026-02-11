ParsePointerType()
{
    Error("pointers was not implemented");
    CheckTokOrDie(TOK_CAP);
    if (!scan.GetToken().IsVar()) Error("identifier expected");
    const Symbol* ref_type = FindSymbolOrDie(scan.GetToken(), SYM_TYPE, "type identifier expected");
    scan.NextToken();
    return new SymTypePointer((SymType*)ref_type);
}
