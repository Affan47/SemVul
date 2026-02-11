multiCondition()
{
    if (!_settings->isEnabled("style"))
        return;

    const SymbolDatabase* const symbolDatabase = _tokenizer->getSymbolDatabase();

    for (std::list<Scope>::const_iterator i = symbolDatabase->scopeList.begin(); i != symbolDatabase->scopeList.end(); ++i) {
        if (i->type != Scope::eIf || !Token::simpleMatch(i->classDef, "if ("))
            continue;

        const Token * const cond1 = i->classDef->next()->astOperand2();

        const Token * tok2 = i->classDef->next();
        while (tok2) {
            tok2 = tok2->link();
            if (!Token::simpleMatch(tok2, ") {"))
                break;
            tok2 = tok2->linkAt(1);
            if (!Token::simpleMatch(tok2, "} else { if ("))
                break;
            tok2 = tok2->tokAt(4);

            if (isOverlappingCond(cond1, tok2->astOperand2(), _settings->library.functionpure))
                multiConditionError(tok2, cond1->linenr());
        }
    }
}
