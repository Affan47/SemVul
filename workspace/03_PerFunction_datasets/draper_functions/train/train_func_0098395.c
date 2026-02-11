closureIdentity( StgClosure *p )
{
    switch (RtsFlags.ProfFlags.doHeapProfile) {

#ifdef PROFILING
    case HEAP_BY_CCS:
	return p->header.prof.ccs;
    case HEAP_BY_MOD:
	return p->header.prof.ccs->cc->module;
    case HEAP_BY_DESCR:
	return GET_PROF_DESC(get_itbl(p));
    case HEAP_BY_TYPE:
	return GET_PROF_TYPE(get_itbl(p));
    case HEAP_BY_RETAINER:


	if (isRetainerSetFieldValid(p))
	    return retainerSetOf(p);
	else
	    return NULL;

#else
    case HEAP_BY_CLOSURE_TYPE:
    {
        StgInfoTable *info;
        info = get_itbl(p);
        switch (info->type) {
        case CONSTR:
        case CONSTR_1_0:
        case CONSTR_0_1:
        case CONSTR_2_0:
        case CONSTR_1_1:
        case CONSTR_0_2:
        case CONSTR_STATIC:
        case CONSTR_NOCAF_STATIC:
            return GET_CON_DESC(itbl_to_con_itbl(info));
        default:
            return closure_type_names[info->type];
        }
    }

#endif
    default:
	barf("closureIdentity");
    }
}
