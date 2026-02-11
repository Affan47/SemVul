add(source, target)
struct symstruct *source;
struct symstruct *target;
{
    scalar_t sscalar;

    if (source->indcount == 0 && source->storage != CONSTANT &&
	(target->indcount != 0 || target->storage & ALLDATREGS))
	swapsym(target, source);
    if ((sscalar = source->type->scalar) & DLONG)
    {
	longop(ADDOP, source, target);
	return;
    }
    if (sscalar & RSCALAR)
    {
	floatop(ADDOP, source, target);
	return;
    }
    if (source->storage == CONSTANT)
    {
	extend(target);
	if (target->indcount != 0 || target->storage & reguse)
	    loadany(target);
	target->offset.offi += (offset_T) source->offset.offv;
    }
    else if (source->indcount == 0)
    {

	sscalar |= target->type->scalar;
	target->type = pctype;
	indexadr(source, target);
    }
    else
    {

	extend(target);
	load(target, DREG);
	outadd();
	movereg(source, DREG);
	if (source->type->scalar & CHAR)
	    adc0();
    }
    target->type = iscalartotype(target->type->scalar | sscalar);
}
