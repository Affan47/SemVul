check_setting(int cond, int no, char *msg, int *ok)
{
	if (!cond)
	{
		logit(LOG_WARNING, MODULE_TAG "%s in account %d", msg, no + 1);
		*ok = 0;
	}
}
