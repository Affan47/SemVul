get_eval_error(const char **str, int *pos)
{
	if (eval_error) {
		if (str) *str = eval_errstr;
		if (pos) *pos = eval_error_pos;
		return eval_error;
	}
	if (str) *str = "?";
	if (pos) *pos = 0;
	return 0;
}
