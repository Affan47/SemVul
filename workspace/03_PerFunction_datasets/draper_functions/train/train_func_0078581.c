quarantine_drain_one(quarantine_t *quarantine)
{
	quarantine_obj_t *obj = &quarantine->objs[quarantine->first];
	assert(obj->usize == isalloc(obj->ptr, config_prof));
	idalloc(obj->ptr);
	quarantine->curbytes -= obj->usize;
	quarantine->curobjs--;
	quarantine->first = (quarantine->first + 1) & ((ZU(1) <<
	    quarantine->lg_maxobjs) - 1);
}
