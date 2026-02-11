Insert(tListItemBase *&a){
    if (anchor)
        Remove();
    anchor = &a;
    next   =  a;
    a      =  this;
    if (next)
        next->anchor = &next;
}
