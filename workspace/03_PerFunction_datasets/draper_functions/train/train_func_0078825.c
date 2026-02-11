add_uses_to_usecounts(Module mp) {
    Module used;
    struct modpart *p;
    for (p=mp->head; p!=NULL; p=p->next)
        if (p->ptype == MODULE) {
            used = lookup(p->contents);
            if (used != NULL)
                used->usecount++;
        }
}
