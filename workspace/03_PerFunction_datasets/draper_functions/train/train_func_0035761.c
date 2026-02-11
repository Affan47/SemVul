nullPointerLinkedList()
{
    const SymbolDatabase* const symbolDatabase = _tokenizer->getSymbolDatabase();


    for (std::list<Scope>::const_iterator i = symbolDatabase->scopeList.begin(); i != symbolDatabase->scopeList.end(); ++i) {
        const Token* const tok1 = i->classDef;

        if (i->type != Scope::eFor || !tok1)
            continue;


        const Token* end2 = tok1->linkAt(1);
        for (const Token *tok2 = tok1->tokAt(2); tok2 != end2; tok2 = tok2->next()) {

            if (Token::Match(tok2, "%var% . %var%")) {

                const unsigned int varid(tok2->varId());
                if (varid == 0)
                    continue;


                const Variable* var = symbolDatabase->getVariableFromVarId(varid);
                if (!var || !var->isPointer())
                    continue;

                if (Token::Match(tok2->tokAt(-2), "%varid% ?", varid))
                    continue;


                for (std::list<Scope*>::const_iterator j = i->nestedList.begin(); j != i->nestedList.end(); ++j) {
                    Scope* scope = *j;
                    if (scope->type != Scope::eWhile)
                        continue;


                    if (Token::Match(scope->classDef->next(), "( %varid% &&|)", varid)) {


                        for (const Token *tok4 = scope->classStart; tok4; tok4 = tok4->next()) {
                            if (tok4 == i->classEnd) {
                                nullPointerError(tok1, var->name(), scope->classDef);
                                break;
                            }


                            else if (tok4->str() == "break" || tok4->str() == "return")
                                break;
                        }
                    }
                }
            }
        }
    }
}
