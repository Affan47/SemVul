ObjectField_add(CTX ctx, kclass_t this_cid, kObject **v, size_t i, ktype_t type, kObject *o)
{
	kclass_t cid = ktype_tocid(ctx, type, this_cid);
	kclass_t bcid = C_bcid(type);
	switch(bcid) {
		case CLASS_Boolean: {
			kunbox_t *nn = (kunbox_t*)(v + i);
			nn[0] = IS_Boolean(o) ? N_tobool(o) : 0;
			break;
		}
		case CLASS_Int: {
			kint_t *nn = (kint_t*)(v + i);
			nn[0] = IS_bInt(o) ? N_toint(o) : 0;
			break;
		}
		case CLASS_Float: {
			kfloat_t *nn = (kfloat_t*)(v + i);
			nn[0] = IS_bFloat(o) ? N_tofloat(o) : KFLOAT_ZERO;
			break;
		}
		case CLASS_Tvoid: {
			break;
		}
		default: {
			if(IS_NOTNULL(o)) {
				KNH_INITv(v[i], o);
			}
			else {
				KNH_INITv(v[i], KNH_NULVAL(cid));
			}
		}
	}
}
