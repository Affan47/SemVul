loadany(source)
struct symstruct *source;
{
    if (source->indcount != 0 || source->offset.offi != 0 ||
	source->level == OFFKLUDGELEVEL || !(source->storage & allregs))
    {
	if (source->type->scalar & RSCALAR)
	    load(source, doubleregs & ~DREG);
	else if ((source->storage == CONSTANT &&
		  !(source->type->scalar & DLONG))
		 || source->type->scalar & CHAR)
	    load(source, DREG);
	else if (source->storage & ~reguse & allregs)
	    load(source, source->storage);
	else if (((reguse & allindregs) == allindregs ||
		  ((!(source->type->constructor & (ARRAY | POINTER)) &&
		  source->indcount != 0) &&
		 !(source->type->scalar & DLONG))))
	    load(source, DREG);
	else
	    load(source, getindexreg());
    }
}
