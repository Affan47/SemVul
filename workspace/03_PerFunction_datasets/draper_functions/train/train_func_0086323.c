isMemberFunc(const Scope *scope, const Token *tok) const
{
    if (tok->function() && tok->function()->nestedIn == scope)
        return !tok->function()->isStatic;


    if (!scope->definedType->derivedFrom.empty()) {

        for (std::size_t i = 0; i < scope->definedType->derivedFrom.size(); ++i) {

            const Type *derivedFrom = scope->definedType->derivedFrom[i].type;


            if (derivedFrom && derivedFrom->classScope && !derivedFrom->hasCircularDependencies()) {
                if (isMemberFunc(derivedFrom->classScope, tok))
                    return true;
            }
        }
    }

    return false;
}
