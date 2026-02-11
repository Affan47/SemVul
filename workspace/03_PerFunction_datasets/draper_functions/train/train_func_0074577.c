pres2(source, target)
struct symstruct *source;
struct symstruct *target;
{
    if (target->storage & allregs)
    {
	if (target->storage & (allregs - allindregs)  ||
	    (target->indcount == 0 &&
	     target->type->scalar & (DLONG | RSCALAR)))
	    push(target);
	else if (((target->storage | reguse) & allindregs) == allindregs)
	{
	    loadpres(target, source);
	    push(target);
	}
	else
	    reguse |= target->storage;
    }
}
