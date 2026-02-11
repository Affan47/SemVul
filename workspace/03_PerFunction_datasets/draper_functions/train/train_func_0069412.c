indirec(source)
struct symstruct *source;
{
    if (!(source->type->constructor & (ARRAY | POINTER)))
	bugerror("illegal indirection");
    else if (source->indcount == (indn_t) - 1)
	limiterror("too many indirections (256)");
    else
    {
	if (source->storage & ALLDATREGS)
	    transfer(source, getindexreg());
	if (!((source->type = source->type->nexttype)->constructor &
	      (ARRAY | FUNCTION)))
	    ++source->indcount;
	if (source->storage == CONSTANT)
	    source->storage = GLOBAL;
    }
}
