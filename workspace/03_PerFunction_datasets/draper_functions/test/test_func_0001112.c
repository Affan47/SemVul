getStack (int level) {
    if (level == 0) {
        return frame ;
    }
    if (level == 1) {
        return staticLink->frame ;
    }
    StaticLink *slink = staticLink ;
    while (slink != NULL && --level > 0) {
        slink = slink->next ;
    }
    if (slink == NULL) {
        std::cerr << "Static link sequence too short - aborting\n" ;
        ::abort() ;

    }
    return slink->frame ;
}
