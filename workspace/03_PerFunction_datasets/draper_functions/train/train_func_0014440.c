velocity_set_bool_opt(u32 * opt, int val, int def, u32 flag,
				  char *name, const char *devname)
{
	(*opt) &= (~flag);
	if (val == -1) {
		printf("%s: set parameter %s to %s\n",
		       devname, name, def ? "TRUE" : "FALSE");
		*opt |= (def ? flag : 0);
	} else if (val < 0 || val > 1) {
		printf
		    ("%s: the value of parameter %s is invalid, the valid range is (0-1)\n",
		     devname, name);
		*opt |= (def ? flag : 0);
	} else {
		printf("%s: set parameter %s to %s\n",
		       devname, name, val ? "TRUE" : "FALSE");
		*opt |= (val ? flag : 0);
	}
}
