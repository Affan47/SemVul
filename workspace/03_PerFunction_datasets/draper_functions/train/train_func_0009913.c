list_active(Variable* const v, Variable* const u) {
    for(Cit it=v->out.begin();it!=v->out.end();++it) {
        Constraint *c=*it;
        if(canFollowRight(c,u)) {
#ifdef LIBVPSC_LOGGING
    ofstream f(LOGFILE,ios::app);
    f<<"  "<<*c<<endl;
#endif
            list_active(c->right,v);
        }
    }
    for(Cit it=v->in.begin();it!=v->in.end();++it) {
        Constraint *c=*it;
        if(canFollowLeft(c,u)) {
#ifdef LIBVPSC_LOGGING
    ofstream f(LOGFILE,ios::app);
    f<<"  "<<*c<<endl;
#endif
            list_active(c->left,v);
        }
    }
}
