Add_Wind (register WIND *w, Object in, Object out) {
    Object inout;
    GC_Node2;

    GC_Link2 (in, out);
    inout = Cons (in, out);
    w->inout = inout;
    w->next = 0;
    if (First_Wind == 0)
        First_Wind = w;
    else
        Last_Wind->next = w;
    w->prev = Last_Wind;
    Last_Wind = w;
    GC_Unlink;
}
