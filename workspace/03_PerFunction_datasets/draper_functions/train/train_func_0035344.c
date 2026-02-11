fconvert(source, type)
struct symstruct *source;
struct typestruct *type;
{
    offset_T spmark;

    pushlist(reguse & OPREG);
    spmark = sp;
    pointat(source);
    if (source->type->scalar & DOUBLE)
	call("dto");
    else
	call("fto");
    if (type->scalar & UNSIGNED)
	outbyte('u');
    outntypechar(type);
    if (type->scalar & DLONG)
    {
	if (reguse & OPREG)
	    bugerror("loading long into used reg");
	source->storage = OPREG;
    }
    else if (type->scalar & CHAR)
	source->storage = BREG;
    else
	source->storage = DREG;
    source->offset.offi =
	source->flags =
	source->indcount = 0;
    modstk(spmark);
    poplist(reguse & OPREG);
}
