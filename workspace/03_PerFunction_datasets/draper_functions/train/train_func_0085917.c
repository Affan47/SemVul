eval_num(struct value *val)
{
	char	*strval, *cp;
	long	nn;

	switch  (val->type)  {
	case  STRING_VALUE:
	case  FSTRING_VALUE:
	case  NAME_VALUE:
	case  CMD_STRING_VALUE:
	case  CMD_NUM_VALUE:
	case  BRACE_VALUE:
		strval = eval_string(val);
		for  (cp = strval;  isspace(*cp);  cp++)
			;
		if  (!isdigit(*cp) && *cp != '-')  {
			if  (debug > 0)
				fprintf(stderr, "String %s returned non-numeric value %s\n", val->val_un.stringval, strval);
			free(strval);
			return  0L;
		}
		nn = atol(cp);
		free(strval);
		return  nn;

	case  NUM_VALUE:
		return  val->val_un.longval;

	case  SNMPVAR_VALUE:
		if  (eval_snmp(val->val_un.stringval) != RES_OK)  {
			if  (debug > 0)
				fprintf(stderr, "SNMP value fetch %s failed\n", val->val_un.stringval);
			return  0L;
		}
		if  (last_result.res_type == RES_TYPE_STRING)  {
			if  (debug > 0)
				fprintf(stderr, "SNMP value of %s is string\n", val->val_un.stringval);
			return  0L;
		}
		if  (last_result.res_type == RES_TYPE_SIGNED)
			return  last_result.res_un.res_signed;

		return  last_result.res_un.res_unsigned;

	case  LASTVAL_VALUE:
		if  (snmp_ok != RES_OK)  {
			if  (debug > 0)
				fprintf(stderr, "Invalid last SNMP value\n");
			return  0L;
		}
		if  (last_result.res_type == RES_TYPE_STRING)  {
			if  (debug > 0)
				fprintf(stderr, "Last SNMP value is string\n");
			return  0L;
		}
		if  (last_result.res_type == RES_TYPE_SIGNED)
			return  last_result.res_un.res_signed;
		return  last_result.res_un.res_unsigned;
	}

	return  0L;
}
