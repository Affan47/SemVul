syntaxCopy()
{
    Expression *e = exp ? exp->syntaxCopy() : NULL;
    DtorExpStatement *es = new DtorExpStatement(loc, e, var);
    return es;
}
