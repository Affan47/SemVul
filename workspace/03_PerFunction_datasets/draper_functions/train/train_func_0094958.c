split_path(
    Variable* r,
    Variable* const v,
    Variable* const u,
    Constraint* &m,
    bool desperation=false
    )
{
    for(Cit it(v->in.begin());it!=v->in.end();++it) {
        Constraint *c=*it;
        if(canFollowLeft(c,u)) {
#ifdef LIBVPSC_LOGGING
    ofstream f(LOGFILE,ios::app);
    f<<"  left split path: "<<*c<<endl;
#endif
            if(c->left==r) {
                if(desperation&&!c->equality) m=c;
                return true;
            } else {
                if(split_path(r,c->left,v,m)) {
                    if(desperation && !c->equality && (!m||c->lm<m->lm)) {
                               m=c;
                    }
                    return true;
                }
            }
        }
    }
    for(Cit it(v->out.begin());it!=v->out.end();++it) {
        Constraint *c=*it;
        if(canFollowRight(c,u)) {
#ifdef LIBVPSC_LOGGING
    ofstream f(LOGFILE,ios::app);
    f<<"  right split path: "<<*c<<endl;
#endif
            if(c->right==r) {
                if(!c->equality) m=c;
                return true;
            } else {
                if(split_path(r,c->right,v,m)) {
                    if(!c->equality && (!m||c->lm<m->lm))
                               m=c;
                    return true;
                }
            }
        }
    }
    return false;
}
