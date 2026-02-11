ParseTypeDeclarations()
{
    while (scan.GetToken().IsVar())
    {
        Token name = scan.GetToken();
        if (FindSymbol(name) != NULL) Error("duplicate declaration");
        CheckNextTokOrDie(TOK_EQUAL);
        SymType* type = ParseType();
        sym_table_stack.back()->Add(new SymTypeAlias(name, type));
        CheckTokOrDie(TOK_SEMICOLON);
    }
}
