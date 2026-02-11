OLCALLPARAMs_typing(CTX ctx, kStmtExpr *stmt, ktype_t tcid, kclass_t new_cid, kMethod *mtd0)
{
	size_t i, size = DP(stmt)->size;
	kMethod *mlists[32] = {NULL}, **mp = mlists;
	kMethod *tmtd = NULL;
	NameSpace_lookupMethods(ctx, K_GMANS, mtd0->cid, mtd0->mn, mlists, 30);
	for(i = 2; i < size; i++) {
		TYPING_UntypedExpr(ctx, stmt, i);
	}
	while(*mp != NULL) {
		kMethod *mtd = mp[0];
		kParam *pa = DP(mtd)->mp;
		if(size - 2 == pa->psize) {
			int status = 0;
			for(i = 0; i < pa->psize; i++) {
				size_t n = i + 2;
				kparam_t* p = knh_Param_get(pa, i);
				ktype_t param_reqt = ktype_tocid(ctx, p->type, new_cid);
				ktype_t type = Tn_type(stmt, n);
				if(type == param_reqt || ClassTBL_isa_(ctx, ClassTBL(type), ClassTBL(param_reqt)) || param_reqt == TYPE_dynamic) {
					continue;
				}
				kTypeMap *tmr =knh_findTypeMapNULL(ctx, type, param_reqt);
				if(tmr != NULL && TypeMap_isSemantic(tmr)) {
					status = 1;
					continue;
				}
				status = 2; break;
			}
			if(status == 0) {
				ktype_t rtype = ktype_tocid(ctx, knh_Param_rtype(pa), new_cid);
				Stmt_typed(ctx, stmt, rtype);
				KNH_SETv(ctx, tkNN(stmt, 0)->data, mtd);
				return CALL_toCONST(ctx, stmt, mtd);
			}
			if(status == 1 && tmtd != NULL) {
				tmtd = mtd;
			}
		}
		mp++;
	}
	if(tmtd != NULL) {
		KNH_SETv(ctx, tkNN(stmt, 0)->data, tmtd);
		return CALLPARAMs_typing(ctx, stmt, tcid, new_cid, tmtd);
	}
	return ERROR_Unsupported(ctx, "no matched method", mtd0->cid, NULL);
}
