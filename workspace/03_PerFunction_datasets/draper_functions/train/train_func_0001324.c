parseShiftExp()
{
    Expression *e;
    Expression *e2;
    Loc loc = token.loc;

    e = parseAddExp();
    while (1)
    {
        switch (token.value)
        {
            case TOKshl:  nextToken(); e2 = parseAddExp(); e = new ShlExp(loc,e,e2);  continue;
            case TOKshr:  nextToken(); e2 = parseAddExp(); e = new ShrExp(loc,e,e2);  continue;
            case TOKushr: nextToken(); e2 = parseAddExp(); e = new UshrExp(loc,e,e2); continue;

            default:
                break;
        }
        break;
    }
    return e;
}
