dumpVariableRef (Variable *var, std::ostream &os) {
    if (var == NULL) {
       dumpWord (-1, os) ;
    } else {

        dumpWord (((Scope*)var->oldValue.ptr)->index, os) ;
        dumpWord (var->offset, os) ;
    }
}
