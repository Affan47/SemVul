Deregister_Object (Object obj) {
    WEAK_NODE *p, **pp;

    Disable_Interrupts;
    for (pp = &first; (p = *pp); ) {
        if (WAS_FORWARDED(p->obj))
            UPDATE_OBJ(p->obj);
        if (EQ(p->obj, obj)) {
            *pp = p->next;
            free ((char *)p);
        } else pp = &p->next;
    }
    Enable_Interrupts;
}
