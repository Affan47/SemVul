message(int num, int pass, const char *api, int retval, char *extra)
{
	char res[10];
	char buf[2*SIZE];
	if (pass)
		strncpy(res, "PASS :", 10);
	else
		strncpy(res, "FAIL :", 10);


	snprintf(buf, sizeof(buf), "cgroup_%s\t\t Ret Value = ", api);
	fprintf(stdout, "TEST%2d:%s %s%d\t%s", num, res, buf, retval, extra);
}
