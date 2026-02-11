NewDtd(void)
{
    Dtd d;

    if(!(d = Malloc(sizeof(*d))))
	return 0;

    d->name = 0;
    d->internal_part = 0;
    d->external_part = 0;
    d->entities = 0;
    d->parameter_entities = 0;
    d->predefined_entities = 0;
#ifdef FOR_LT
    d->doctype = 0;
#else
    d->elements = 0;
#endif
    d->notations = 0;

    return d;
}
