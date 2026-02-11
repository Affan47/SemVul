showvars (int sp, StackFrame *f) {
    Scope::VarMap::iterator i ;
    Scope *scope = scopeStack[sp-1] ;
    Value *base = f->varstack ;
    for (i = scope->variables.begin() ; i != scope->variables.end() ; i++) {
        Variable *var = i->second ;
        if (var->name[0] == '.') {
            continue ;
        }
        Value &v = base[var->offset] ;
        if (v.type == T_FUNCTION || v.type == T_CLASS ||
            v.type == T_THREAD || v.type == T_MONITOR ||
            v.type == T_PACKAGE || v.type == T_INTERFACE ||
            v.type == T_ENUMCONST) {
            continue ;
        }
        if (var->name == "this" || var->name[0] == '.') {
           continue ;
        }

        if (var->flags & VAR_CONST) {
            continue ;
        }
        std::cout << scope->majorScope->fullname << '.' << var->name << " = " ;
        printValue (std::cout, v) ;
        std::cout << "\n" ;
    }
}
