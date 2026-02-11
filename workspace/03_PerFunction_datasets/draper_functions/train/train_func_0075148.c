isParentBlock (Block *block) {
    Block *b = scopeStack[scopeSP-1]->majorScope ;
    while (b != NULL) {
	if (b == block) {
            return true ;
	}
	b = b->parentBlock ;
    }
    return false ;

}
