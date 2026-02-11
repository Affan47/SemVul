getFQDNName(SPtr<TDUID> duid) {
    int cpt = 1;
    string res = "";
    SPtr<TFQDN> foo = FQDNLst.getFirst();
    FQDNLst.first();
    foo = FQDNLst.get();
    while(!(*(*foo).Duid == *duid) && cpt<FQDNLst.count()){
        foo = FQDNLst.get();
 	cpt++;
    }
    if (cpt<FQDNLst.count()) {
        res = (*foo).Name;
    } else {
        if (*(*foo).Duid == *duid) {
	    res = (*foo).Name;
	}
    }
    return res;
}
