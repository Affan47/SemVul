make_restrictinfo(Expr *clause,
				  bool is_pushed_down,
				  bool outerjoin_delayed,
				  bool pseudoconstant,
				  Relids required_relids)
{


	if (or_clause((Node *) clause))
		return (RestrictInfo *) make_sub_restrictinfos(clause,
													   is_pushed_down,
													   outerjoin_delayed,
													   pseudoconstant,
													   required_relids);


	Assert(!and_clause((Node *) clause));

	return make_restrictinfo_internal(clause,
									  NULL,
									  is_pushed_down,
									  outerjoin_delayed,
									  pseudoconstant,
									  required_relids);
}
