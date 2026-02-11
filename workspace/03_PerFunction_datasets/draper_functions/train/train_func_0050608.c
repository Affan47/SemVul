knh_opline_reftrace(CTX ctx, kopl_t *c FTRARG)
{
	if(FLAG_is(OPDATA[c->opcode].flag, _CONST)) {
		size_t i, size = OPDATA[c->opcode].size;
		for(i = 0; i < size; i++) {
			kushort_t vtype = OPDATA[c->opcode].types[i];
			if(vtype == VMT_OBJECT || vtype == VMT_STRING) {
				KNH_ADDREF(ctx, c->p[i]);
			}
		}
	}
	return tail_;
}
