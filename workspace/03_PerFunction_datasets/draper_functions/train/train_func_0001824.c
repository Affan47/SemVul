add2seen (dnode_t *cnode) {
    if (seeni >= seenn) {
        seenp = Marraygrow (seenp, (long) (seenn + SEENINCR) * SEENSIZE);
        seenn += SEENINCR;
    }
    seenp[seeni].vo = cnode->vo;
    seenp[seeni++].path = cnode->path;
}
