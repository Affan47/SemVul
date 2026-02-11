checkFunctionCall(const Token *tok, const ArrayInfo &arrayInfo, std::list<const Token *> callstack)
{


    if (callstack.size() >= 2)
        return;


    for (std::list<const Token*>::const_iterator it = callstack.begin(); it != callstack.end(); ++it) {

        if (tok->str() == (*it)->str())
            return;
    }
    callstack.push_back(tok);

    const unsigned int declarationId = arrayInfo.declarationId();

    const Token *tok2 = tok->tokAt(2);

    if (Token::Match(tok2, "%varid% ,|)", declarationId))
        checkFunctionParameter(*tok, 1, arrayInfo, callstack);
    else if (Token::Match(tok2, "%varid% + %num% ,|)", declarationId)) {
        const ArrayInfo ai(arrayInfo.limit(MathLib::toLongNumber(tok2->strAt(2))));
        checkFunctionParameter(*tok, 1, ai, callstack);
    }


    tok2 = tok2->nextArgument();
    if (Token::Match(tok2, "%varid% ,|)", declarationId))
        checkFunctionParameter(*tok, 2, arrayInfo, callstack);
    else if (Token::Match(tok2, "%varid% + %num% ,|)", declarationId)) {
        const ArrayInfo ai(arrayInfo.limit(MathLib::toLongNumber(tok2->strAt(2))));
        checkFunctionParameter(*tok, 2, ai, callstack);
    }
}
