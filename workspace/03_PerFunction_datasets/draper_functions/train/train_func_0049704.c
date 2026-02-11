addRegistrar(XMLNode node) {

    InfoRegistrar* r = new InfoRegistrar(node);
    if(!(r)) {
         delete r;
         return NULL;
    }
    regr_.push_back(r);
    CreateThreadFunction(&reg_thread, r);
    return r;
}
