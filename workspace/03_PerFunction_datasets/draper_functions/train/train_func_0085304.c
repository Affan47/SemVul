changeDebugContext(Dir d, ExecState* exec, Node* n) {
    FunctionBodyNode* body = static_cast<FunctionBodyNode*>(n);
    Debugger* dbg = exec->dynamicInterpreter()->debugger();
    List args;
    FunctionImp* fn = 0;


    const ScopeChain& chain = exec->scopeChain();
    for (ScopeChainIterator iter = chain.begin(); iter != chain.end(); ++iter) {
        JSObject* scopeObj = *iter;

        if (scopeObj->isActivation()) {
            ActivationImp* act = static_cast<ActivationImp*>(scopeObj);
            args = act->passedInArguments();
            fn   = static_cast<FunctionImp*>(act->function());
            break;
        }
    }

    if (d == Enter)
        dbg->enterContext(exec, body->sourceId(), body->firstLine(), fn, args);
    else
        dbg->exitContext(exec, body->sourceId(), body->lastLine(), fn);
}
