parseAssignExp()
{
    Expression *e;
    Expression *e2;
    Loc loc;

    e = parseCondExp();
    while (1)
    {
        loc = token.loc;
        switch (token.value)
        {
#define X(tok,ector) \
            case tok:  nextToken(); e2 = parseAssignExp(); e = new ector(loc,e,e2); continue;

            X(TOKassign,    AssignExp);
            X(TOKaddass,    AddAssignExp);
            X(TOKminass,    MinAssignExp);
            X(TOKmulass,    MulAssignExp);
            X(TOKdivass,    DivAssignExp);
            X(TOKmodass,    ModAssignExp);
            X(TOKpowass,    PowAssignExp);
            X(TOKandass,    AndAssignExp);
            X(TOKorass,     OrAssignExp);
            X(TOKxorass,    XorAssignExp);
            X(TOKshlass,    ShlAssignExp);
            X(TOKshrass,    ShrAssignExp);
            X(TOKushrass,   UshrAssignExp);
            X(TOKcatass,    CatAssignExp);

#undef X
            default:
                break;
        }
        break;
    }
    return e;
}
