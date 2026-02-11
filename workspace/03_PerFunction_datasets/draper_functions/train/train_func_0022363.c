printStaticLinks (StaticLink *slink) {
    int i = 0;
    do {
        std::cerr << "SLINK " << (i++) << ": next: " << slink->next << ", frame: " << slink->frame << " (" << slink->frame->block->name << ")\n";
        slink = slink->next;
    } while (slink != NULL && slink->frame->block->name != "main");
    if (slink != NULL) {
        std::cerr << "SLINK " << (i++) << ": next: " << slink->next << ", frame: " << slink->frame << " (" << slink->frame->block->name << ")\n";
    }
}
