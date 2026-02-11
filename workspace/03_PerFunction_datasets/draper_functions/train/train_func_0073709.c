splitBetween(Variable* const vl, Variable* const vr,
               Block* &lb, Block* &rb) {
#ifdef LIBVPSC_LOGGING
    ofstream f(LOGFILE,ios::app);
    f<<"  need to split between: "<<*vl<<" and "<<*vr<<endl;
#endif
    Constraint *c=findMinLMBetween(vl, vr);
#ifdef LIBVPSC_LOGGING
    f<<"  going to split on: "<<*c<<endl;
#endif
    if(c!=NULL) {
        split(lb,rb,c);
        deleted = true;
    }
    return c;
}
