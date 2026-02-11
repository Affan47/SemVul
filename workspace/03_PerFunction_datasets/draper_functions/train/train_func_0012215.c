get_variable (const char *begin, size_t len,
				      struct var_data *vdt)
{
struct var_data *vdp;

	if (!begin || !vdt)
	{
		err("authpgsql: critical error while "
				 "parsing substitution variable");
		return NULL;
	}
	if (len < 1)
	{
		err("authpgsql: unknown empty substitution "
				 "variable - aborting");
		return NULL;
	}
	if (len > MAX_SUBSTITUTION_LEN)
	{
		err("authpgsql: variable name too long "
				 "while parsing substitution. "
				 "name begins with "
				 SV_BEGIN_MARK
				 "%.*s...", MAX_SUBSTITUTION_LEN, begin);
		return NULL;
	}

	for (vdp=vdt; vdp->name; vdp++)
		if (vdp->size == len+1 &&
		    !strncmp(begin, vdp->name, len))
		{
			if (!vdp->value)
				vdp->value = "";
			return vdp;
		}

	err("authpgsql: unknown substitution variable "
			 SV_BEGIN_MARK
			 "%.*s"
			 SV_END_MARK
			 , (int)len, begin);

	return NULL;
}
