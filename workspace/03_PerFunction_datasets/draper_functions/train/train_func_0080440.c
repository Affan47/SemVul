findMacro (const string &nm, Package *&pkg) {
    Macro *macro = Scope::findMacro (nm, pkg) ;
    if (macro != NULL) {
        return macro ;
    }
    if (superblock != NULL) {
        return superblock->block->findMacro (nm, pkg) ;
    }
    return NULL ;
}
