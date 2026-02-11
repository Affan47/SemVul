replace(Token *replaceThis, Token *start, Token *end)
{

    if (start->previous())
        start->previous()->next(end->next());

    if (end->next())
        end->next()->previous(start->previous());


    if (replaceThis->previous())
        replaceThis->previous()->next(start);

    if (replaceThis->next())
        replaceThis->next()->previous(end);

    start->previous(replaceThis->previous());
    end->next(replaceThis->next());

    if (end->tokensBack && *(end->tokensBack) == end) {
        while (end->next())
            end = end->next();
        *(end->tokensBack) = end;
    }


    for (Token *tok = start; tok != end->next(); tok = tok->next())
        tok->_progressValue = replaceThis->_progressValue;


    delete replaceThis;
}
