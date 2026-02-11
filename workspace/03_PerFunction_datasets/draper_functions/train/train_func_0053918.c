addlist(UDlist *udlst, int aryno, symbol_kind arykind, Pa_object *pa_object,
	int cef, int min, int max, int arydim)
{
    UDlist *tpnew;
    UDlist *findptr;

    if(localize_with_pa)
	findptr = lookupary_pa(udlst, aryno, arykind, arydim, pa_object);
    else
        findptr = lookupary(udlst, aryno, arykind, arydim);

    if (findptr != NULL) {
        if (findptr->cef != cef) {
            if (localize_verbose > 1){
                fprintf(stderr, "CEF Error\n");
	    }
            findptr->cef = CEF_ERROR;
        }

        if (findptr->min > min)
            findptr->min = min;
        if (findptr->max < max)
            findptr->max = max;
    }
    else{
        tpnew = construct_udlist(aryno, arykind, cef, min, max, arydim, pa_object);
        udlst = append_udlist(udlst, tpnew);
    }

    return udlst;
}
