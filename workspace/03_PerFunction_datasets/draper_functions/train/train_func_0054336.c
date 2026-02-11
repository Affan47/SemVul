check()
{

    const std::size_t functions = symbolDatabase->functionScopes.size();
    for (std::size_t i = 0; i < functions; ++i) {
        const Scope * scope = symbolDatabase->functionScopes[i];

        checkScope(scope->classStart->next(), "", 0, scope->functionOf != nullptr, 1);
    }


    for (unsigned int i = 1; i < symbolDatabase->getVariableListSize(); i++) {
        const Variable* var = symbolDatabase->getVariableFromVarId(i);
        if (!var || (!var->isLocal() && !var->isArgument()) || var->isStatic() || !var->scope())
            continue;

        if (var->isReference())
            continue;

        if (!var->isPointer() && var->typeStartToken()->str() != "int")
            continue;


        if (var->isPointer() && var->type() && !var->typeScope())
            continue;

        unsigned int sz = _tokenizer->sizeOfType(var->typeStartToken());
        if (sz < 1)
            sz = 1;

        if (var->isArgument())
            checkScope(var->scope()->classStart->next(), var->name(), i, isInMemberFunc(var->scope()), sz);
        else
            checkScope(var->nameToken(), var->name(), i, isInMemberFunc(var->scope()), sz);
    }
}
