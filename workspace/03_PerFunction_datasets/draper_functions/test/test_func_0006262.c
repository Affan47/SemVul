print_tc_classid(char *buf, int len, __u32 h)
{
	if (h == TC_H_ROOT)
		sprintf(buf, "root");
	else if (h == TC_H_UNSPEC)
		snprintf(buf, len, "none");
	else if (TC_H_MAJ(h) == 0)
		snprintf(buf, len, ":%x", TC_H_MIN(h));
	else if (TC_H_MIN(h) == 0)
		snprintf(buf, len, "%x:", TC_H_MAJ(h)>>16);
	else
		snprintf(buf, len, "%x:%x", TC_H_MAJ(h)>>16, TC_H_MIN(h));
	return 0;
}
