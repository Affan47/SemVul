ObjectFieldN_initcopy(CTX ctx, kRawPtr *o, kRawPtr *src)
{
	kObject *of = (kObject*)o;
	const knh_ClassTBL_t *ct = O_cTBL(o);
	if(ct->fsize > 0) {
		Object **v = &(of->smallobject);
		if(ct->fsize > K_SMALLOBJECT_FIELDSIZE) {
			v = (Object**)KNH_MALLOC(ctx, ct->fsize * sizeof(kObject*));
		}
		of->fields = v;
		knh_memcpy(v, src->rawptr, ct->fsize * sizeof(kObject*));
	}
	else {
		of->fields = NULL;
	}
}
