isSubclassOrImplements (Block *b) {
    if (this == b) {
        return true ;
    }
    if (isSuperBlock (b)) {
        return true ;
    }

    if (b->type == T_INTERFACE) {
        Block *blk = this ;
        while (blk != NULL) {
            if (blk->implementsInterface (b)) {
                return true ;
            }
            if (blk->superblock == NULL) {
                break ;
            }
            blk = blk->superblock->block ;
        }
    }
    return false ;
}
