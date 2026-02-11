obj_desc_pval(const object_type *o_ptr, char *buf, size_t max, size_t end)
{
	bitflag f[OF_SIZE];

	object_flags(o_ptr, f);

	if (!flags_test(f, OF_SIZE, OF_PVAL_MASK, FLAG_END)) return end;

	strnfcat(buf, max, &end, " (%+d", o_ptr->pval);

	if (!of_has(f, OF_HIDE_TYPE))
	{
		if (of_has(f, OF_STEALTH))
			strnfcat(buf, max, &end, " stealth");
		else if (of_has(f, OF_SEARCH))
			strnfcat(buf, max, &end, " searching");
		else if (of_has(f, OF_INFRA))
			strnfcat(buf, max, &end, " infravision");
		else if (of_has(f, OF_SPEED))
			strnfcat(buf, max, &end, " speed");
		else if (of_has(f, OF_BLOWS))
			strnfcat(buf, max, &end, " attack%s", PLURAL(o_ptr->pval));
	}

	strnfcat(buf, max, &end, ")");

	return end;
}
