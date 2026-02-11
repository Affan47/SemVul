Event_Predicate (Display *dpy, XEvent *ep,
#ifdef XLIB_RELEASE_5_OR_LATER
                XPointer ptr) {
#else
                char *ptr) {
#endif
    struct predicate_arg *ap = (struct predicate_arg *)ptr;
    register int i;
    Object args;
    GC_Node;

    if ((i = ep->type) < LASTEvent && !Nullp (ap->funcs[i])) {
        args = Get_Event_Args (ep);
        GC_Link (args);
        *ap->ret = Funcall (ap->funcs[i], args, 0);
        Destroy_Event_Args (args);
        GC_Unlink;
    }
    return Truep (*ap->ret);
}
