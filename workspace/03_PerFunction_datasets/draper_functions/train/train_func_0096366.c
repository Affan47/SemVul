isBaseClassFunc(const Token *tok, const Scope *scope)
{

    for (std::size_t i = 0; i < scope->definedType->derivedFrom.size(); ++i) {
        const Type *derivedFrom = scope->definedType->derivedFrom[i].type;


        if (derivedFrom && derivedFrom->classScope) {
            const std::list<Function>& functionList = derivedFrom->classScope->functionList;
            std::list<Function>::const_iterator func;

            for (func = functionList.begin(); func != functionList.end(); ++func) {
                if (func->tokenDef->str() == tok->str())
                    return true;
            }
        }


        else
            return true;
    }

    return false;
}
