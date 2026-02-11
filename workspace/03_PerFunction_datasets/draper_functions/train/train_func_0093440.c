concat
	(
	Uc_expression *e
	)
	{
	Uc_array_expression *arr = dynamic_cast<Uc_array_expression *> (e);
	if (!arr)
		add(e);
	else
		{
		for (std::vector<Uc_expression *>::iterator it =
			arr->exprs.begin(); it != arr->exprs.end(); it++)
			add(*it);
		arr->exprs.clear();
		delete arr;
		}
	}
