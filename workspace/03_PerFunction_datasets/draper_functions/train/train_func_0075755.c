knh_NameSpace_getFmtNULL(CTX ctx, kNameSpace *ns, kclass_t cid, kmethodn_t mn)
{
	L_TAIL:;
	if(DP(ns)->formattersNULL != NULL) {
		kArray *a = DP(ns)->formattersNULL;
		size_t i;
		for(i = 0; i < knh_Array_size(a); i++) {
			kMethod *mtd = a->methods[i];
			if((mtd)->cid == cid && (mtd)->mn == mn) {
				return mtd;
			}
		}
	}
	if(ns->parentNULL != NULL) {
		ns = ns->parentNULL;
		goto L_TAIL;
	}
	return knh_ClassTBL_getFmtNULL(ctx, ClassTBL(cid), mn);
}
