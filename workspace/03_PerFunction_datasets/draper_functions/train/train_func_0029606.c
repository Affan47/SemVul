merge(Block* b, Constraint* c) {
#ifdef LIBVPSC_LOGGING
    ofstream f(LOGFILE,ios::app);
    f<<"  merging on: "<<*c<<",c->left->offset="<<c->left->offset<<",c->right->offset="<<c->right->offset<<endl;
#endif
    double dist = c->right->offset - c->left->offset - c->gap;
    Block *l=c->left->block;
    Block *r=c->right->block;
    if (l->vars->size() < r->vars->size()) {
        r->merge(l,c,dist);
    } else {
               l->merge(r,c,-dist);
    }
    Block* mergeBlock=b->deleted?this:b;
#ifdef LIBVPSC_LOGGING
    f<<"  merged block="<<*mergeBlock<<endl;
#endif
    return mergeBlock;
}
