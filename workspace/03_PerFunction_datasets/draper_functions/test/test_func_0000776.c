str_to_context(char *string, ulong *value, struct task_context **tcp)
{
	ulong dvalue, hvalue;
	int found, type;
	char *s;
	struct task_context *tc_dp, *tc_dt, *tc_hp, *tc_ht;

	if (string == NULL) {
		error(INFO, "received NULL string\n");
		return STR_INVALID;
	}

	s = string;
        dvalue = hvalue = BADADDR;

        if (decimal(s, 0))
                dvalue = dtol(s, RETURN_ON_ERROR, NULL);

        if (hexadecimal(s, 0)) {
        	if (STRNEQ(s, "0x") || STRNEQ(s, "0X"))
                	s += 2;
		if (strlen(s) <= MAX_HEXADDR_STRLEN)
                	hvalue = htol(s, RETURN_ON_ERROR, NULL);
	}

        found = 0;
        tc_dp = tc_dt = tc_hp = tc_ht = NULL;
	type = STR_INVALID;

	if (dvalue != BADADDR) {
		if ((tc_dp = pid_to_context(dvalue)))
			found++;
	        if ((tc_dt = task_to_context(dvalue)))
			found++;
	}

	if ((hvalue != BADADDR) && (dvalue != hvalue)) {
	        if ((tc_hp = pid_to_context(hvalue)))
			found++;
	        if ((tc_ht = task_to_context(hvalue)))
			found++;
	}

	switch (found)
	{
	case 2:
		if (tc_dp && tc_hp) {
                	*tcp = tc_dp;
                	*value = dvalue;
                	type = STR_PID;
		}
		break;

	case 1:
		if (tc_dp) {
			*tcp = tc_dp;
			*value = dvalue;
			type = STR_PID;
		}

		if (tc_dt) {
			*tcp = tc_dt;
			*value = dvalue;
			type = STR_TASK;
		}

		if (tc_hp) {
			*tcp = tc_hp;
			*value = hvalue;
			type = STR_PID;
		}

		if (tc_ht) {
			*tcp = tc_ht;
			*value = hvalue;
			type = STR_TASK;
		}
		break;
	}

	return type;
}
