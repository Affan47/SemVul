add_proto_to_mask(int proto){
	unsigned int i=0, flag=0;

	for (i = 0; i < ARRAY_SIZE(chain_flags); ++i)
			if (proto == chain_flags[i].proto){
				flag = chain_flags[i].flag;
				break;
			}

	if (i == ARRAY_SIZE(chain_flags))
		xtables_error(PARAMETER_PROBLEM,
		"unknown header `%d' specified",
		proto);

	return flag;
}
