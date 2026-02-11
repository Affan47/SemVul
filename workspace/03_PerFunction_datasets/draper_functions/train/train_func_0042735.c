lookupary_pa(UDlist *udlst, int aryno, symbol_kind arykind, int arydim, Pa_object *pa_object)
{
    UDlist *p;

    for (p = udlst; p != NULL; p = p->next) {
	if(p->pa_object != NULL) {
	    if (p->pa_object->entry == aryno &&
		p->arydim == arydim &&
		p->pa_object->kind == arykind ) {

		break;
	    }
	} else {
	    if (p->aryno == aryno && p->arydim == arydim
		&& p->arykind == arykind )
		break;
	}
    }

    return p;
}
