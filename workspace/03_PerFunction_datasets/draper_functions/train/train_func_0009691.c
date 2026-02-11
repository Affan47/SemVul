select_equality_operator(EquivalenceClass *ec, Oid lefttype, Oid righttype)
{
	ListCell   *lc;

	foreach(lc, ec->ec_opfamilies)
	{
		Oid			opfamily = lfirst_oid(lc);
		Oid			opno;

		opno = get_opfamily_member(opfamily, lefttype, righttype,
								   BTEqualStrategyNumber);
		if (OidIsValid(opno))
			return opno;
	}
	return InvalidOid;
}
