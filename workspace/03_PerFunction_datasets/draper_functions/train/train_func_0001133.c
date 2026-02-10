pbx_checkcondition(const char *condition)
{
	int res;
	if (ast_strlen_zero(condition)) {
		return 0;
	} else if (sscanf(condition, "%30d", &res) == 1) {
		return res;
	} else {
		return 1;
	}
}
