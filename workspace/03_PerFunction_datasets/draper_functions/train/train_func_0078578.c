checkDuplicateBranch()
{


    if (!_settings->isEnabled("style") || !_settings->inconclusive)
        return;

    const SymbolDatabase *symbolDatabase = _tokenizer->getSymbolDatabase();

    std::list<Scope>::const_iterator scope;

    for (scope = symbolDatabase->scopeList.begin(); scope != symbolDatabase->scopeList.end(); ++scope) {
        if (scope->type != Scope::eIf)
            continue;


        if (Token::simpleMatch(scope->classEnd, "} else {")) {


            bool macro = false;
            for (const Token *tok = scope->classStart; tok != scope->classEnd->linkAt(2); tok = tok->next()) {
                if (tok->isExpandedMacro()) {
                    macro = true;
                    break;
                }
            }
            if (macro)
                continue;


            std::string branch1 = scope->classStart->next()->stringifyList(scope->classEnd);


            std::string branch2 = scope->classEnd->tokAt(3)->stringifyList(scope->classEnd->linkAt(2));


            if (!branch1.empty() && branch1 == branch2)
                duplicateBranchError(scope->classDef, scope->classEnd->next());
        }
    }
}
