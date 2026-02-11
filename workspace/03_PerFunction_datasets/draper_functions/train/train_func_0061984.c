newmodule (char *modname) {
    Module p = (Module) malloc (sizeof (struct module));
    checkptr(p);
    p->name = strsave(modname);
    p->usecount = 0;
    p->head = p->tail = NULL;
    return p;
}
