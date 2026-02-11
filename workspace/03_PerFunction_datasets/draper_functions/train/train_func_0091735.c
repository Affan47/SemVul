parseOrExp()
{
    Loc loc = token.loc;

    Expression *e = parseXorExp();
    while (token.value == TOKor)
    {
        checkParens(TOKor, e);
        nextToken();
        Expression *e2 = parseXorExp();
        checkParens(TOKor, e2);
        e = new OrExp(loc, e, e2);
    }
    return e;
}
