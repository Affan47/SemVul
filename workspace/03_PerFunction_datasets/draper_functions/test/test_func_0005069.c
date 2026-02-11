gen_call
	(
	vector<char>& out,
	Uc_function *fun,
	bool orig,
	Uc_expression *itemref,
	Uc_array_expression *parms,
	bool retvalue
	)
	{
	int parmcnt = 0;
	if (itemref)
		Uc_location::yyerror("Can't use ITEM for intrinsic");

	const std::vector<Uc_expression *>& exprs = parms->get_exprs();

	for (std::vector<Uc_expression *>::const_reverse_iterator it =
			exprs.rbegin(); it != exprs.rend(); it++)
		{
		Uc_expression *expr = *it;
		expr->gen_value(out);
		parmcnt++;
		}


	out.push_back((char) (retvalue ? UC_CALLIS : UC_CALLI));
	Write2(out, intrinsic_num);
	out.push_back((char) parmcnt);
	return 1;
	}
