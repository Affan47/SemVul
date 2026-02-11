push_parent(AV *parents, SV * obj, HV * refcounters) {
    char name[64];
    int result;
    int name_len = sprintf(name, "%p", SvRV(obj));

    if (hv_exists(refcounters, name, name_len)) {
    	SV * value = (SV *)*hv_fetch(refcounters, name, name_len, 0);
    	result = SvIV(value) + 1;
    	sv_setiv(value, result);
    } else {
    	(void) hv_store(refcounters, name, name_len, newSViv(1), 0);
    	result = 1;
    }


    av_push(parents, obj);
    return result;
}
