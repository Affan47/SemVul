ParseArrayType()
{
    std::vector<std::pair<int, int> > bounds;
    CheckTokOrDie(TOK_ARRAY);
    CheckTokOrDie(TOK_BRACKETS_SQUARE_LEFT);
    bool was_comma = true;
    while (was_comma)
    {
        int fst = GetIntConstValueOrDie();
        CheckTokOrDie(TOK_DOUBLE_DOT);
        int sec = GetIntConstValueOrDie();
        if (sec < fst) Error("invalid subrange type");
        bounds.push_back(std::pair<int, int>(fst, sec));
        if (was_comma = (scan.GetToken().GetValue() == TOK_COMMA)) scan.NextToken();
    }
    CheckTokOrDie(TOK_BRACKETS_SQUARE_RIGHT);
    CheckTokOrDie(TOK_OF);
    SymType* res = ParseType();
    for (std::vector<std::pair<int, int> >::reverse_iterator it = bounds.rbegin(); it != bounds.rend(); ++it)
        res = new SymTypeArray(res, it->first, it->second);
    return res;
}
