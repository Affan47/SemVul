addGlobalFunction(Scope*& scope, const Token*& tok, const Token *argStart, const Token* funcStart)
{
    Function* function = 0;
    for (std::list<Function>::iterator i = scope->functionList.begin(); i != scope->functionList.end(); ++i) {
        if (i->tokenDef->str() == tok->str() && Function::argsMatch(scope, i->argDef->next(), argStart->next(), "", 0))
            function = &*i;
    }

    if (!function)
        function = addGlobalFunctionDecl(scope, argStart, funcStart);

    function->arg = argStart;
    function->token = funcStart;
    function->hasBody = true;

    addNewFunction(&scope, &tok);

    if (scope) {
        scope->function = function;
        function->functionScope = scope;
        return function;
    }
    return 0;
}
