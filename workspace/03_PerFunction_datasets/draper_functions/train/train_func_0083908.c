OPEQ_bcid(CTX ctx, kStmtExpr *stmt)
{
	kclass_t cid1 = Tn_cid(stmt, 1);
	kclass_t cid2 = Tn_cid(stmt, 2);
	kclass_t bcid1 = C_bcid(cid1);
	kclass_t bcid2 = C_bcid(cid2);
	if(cid1 == cid2) return cid1;
	if(cid1 == CLASS_Tdynamic || cid2 == CLASS_Tdynamic) return CLASS_Tdynamic;
	if(bcid1 == cid2) return bcid1;
	if(bcid2 == cid1) return bcid2;
	if(bcid1 == CLASS_Float && bcid2 == CLASS_Int) return cid1;
	if(bcid2 == CLASS_Float && bcid1 == CLASS_Int) return cid2;
	return CLASS_unknown;
}
