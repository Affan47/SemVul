createVariable (StackFrame *stack, std::string name, Value &value, Token access, bool isconst, bool isgeneric) {
    stack->checkCapacity() ;

    Variable *var = new Variable (name, stack->block->stacksize++) ;
    stack->block->insertVariable (var) ;
    addVariableName (name, stack->block, var) ;

    var->setValue (value, stack) ;


    var->setAccess (access) ;
    if (isconst) {
        var->flags |= VAR_CONST ;
    }
    if (isgeneric) {
        var->flags |= VAR_GENERIC ;
    }
}
