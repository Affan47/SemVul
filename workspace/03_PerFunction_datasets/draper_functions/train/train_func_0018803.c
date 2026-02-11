fiu_rc_string(const char *cmd, char ** const error)
{
	char m_cmd[MAX_LINE];
	char command[MAX_LINE], parameters[MAX_LINE];


	strncpy(m_cmd, cmd, MAX_LINE);


	{
		char *tok = NULL, *state = NULL;

		tok = strtok_r(m_cmd, " \t", &state);
		if (tok == NULL) {
			*error = "Cannot get command";
			return -1;
		}
		strncpy(command, tok, MAX_LINE);

		tok = strtok_r(NULL, " \t", &state);
		if (tok == NULL) {
			*error = "Cannot get parameters";
			return -1;
		}
		strncpy(parameters, tok, MAX_LINE);
	}


	char *fp_name = NULL;
	int failnum = 1;
	void *failinfo = NULL;
	unsigned int flags = 0;
	double probability = -1;
	char *func_name = NULL;
	int func_pos_in_stack = -1;

	{

		enum {
			OPT_NAME = 0,
			OPT_FAILNUM,
			OPT_FAILINFO,
			OPT_PROBABILITY,
			OPT_FUNC_NAME,
			OPT_POS_IN_STACK,
			FLAG_ONETIME,
		};
		char * const token[] = {
			[OPT_NAME] = "name",
			[OPT_FAILNUM] = "failnum",
			[OPT_FAILINFO] = "failinfo",
			[OPT_PROBABILITY] = "probability",
			[OPT_FUNC_NAME] = "func_name",
			[OPT_POS_IN_STACK] = "pos_in_stack",
			[FLAG_ONETIME] = "onetime",
			NULL
		};

		char *value;
		char *opts = parameters;
		while (*opts != '\0') {
			switch (getsubopt(&opts, token, &value)) {
			case OPT_NAME:
				fp_name = value;
				break;
			case OPT_FAILNUM:
				failnum = atoi(value);
				break;
			case OPT_FAILINFO:
				failinfo = (void *) strtoul(value, NULL, 10);
				break;
			case OPT_PROBABILITY:
				probability = strtod(value, NULL);
				break;
			case OPT_FUNC_NAME:
				func_name = value;
				break;
			case OPT_POS_IN_STACK:
				func_pos_in_stack = atoi(value);
				break;
			case FLAG_ONETIME:
				flags |= FIU_ONETIME;
				break;
			default:
				*error = "Unknown parameter";
				return -1;
			}
		}
	}


	if (strcmp(command, "disable") == 0) {
		return fiu_disable(fp_name);
	} else if (strcmp(command, "enable") == 0) {
		return fiu_enable(fp_name, failnum, failinfo, flags);
	} else if (strcmp(command, "enable_random") == 0) {
		return fiu_enable_random(fp_name, failnum, failinfo,
				flags, probability);
	} else if (strcmp(command, "enable_stack_by_name") == 0) {
		return fiu_enable_stack_by_name(fp_name, failnum, failinfo,
				flags, func_name, func_pos_in_stack);
	} else {
		*error = "Unknown command";
		return -1;
	}
}
