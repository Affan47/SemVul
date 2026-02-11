print_uptimestr(int fd, struct timeval timeval, const char *prefix, int printsec)
{
	int x;
	struct ast_str *out;

#define SECOND (1)
#define MINUTE (SECOND*60)
#define HOUR (MINUTE*60)
#define DAY (HOUR*24)
#define WEEK (DAY*7)
#define YEAR (DAY*365)
#define NEEDCOMMA(x) ((x)? ",": "")
	if (timeval.tv_sec < 0)
		return;

	if (printsec)  {
		ast_cli(fd, "%s: %lu\n", prefix, (u_long)timeval.tv_sec);
		return;
	}
	out = ast_str_alloca(256);
	if (timeval.tv_sec > YEAR) {
		x = (timeval.tv_sec / YEAR);
		timeval.tv_sec -= (x * YEAR);
		ast_str_append(&out, 0, "%d year%s%s ", x, ESS(x),NEEDCOMMA(timeval.tv_sec));
	}
	if (timeval.tv_sec > WEEK) {
		x = (timeval.tv_sec / WEEK);
		timeval.tv_sec -= (x * WEEK);
		ast_str_append(&out, 0, "%d week%s%s ", x, ESS(x),NEEDCOMMA(timeval.tv_sec));
	}
	if (timeval.tv_sec > DAY) {
		x = (timeval.tv_sec / DAY);
		timeval.tv_sec -= (x * DAY);
		ast_str_append(&out, 0, "%d day%s%s ", x, ESS(x),NEEDCOMMA(timeval.tv_sec));
	}
	if (timeval.tv_sec > HOUR) {
		x = (timeval.tv_sec / HOUR);
		timeval.tv_sec -= (x * HOUR);
		ast_str_append(&out, 0, "%d hour%s%s ", x, ESS(x),NEEDCOMMA(timeval.tv_sec));
	}
	if (timeval.tv_sec > MINUTE) {
		x = (timeval.tv_sec / MINUTE);
		timeval.tv_sec -= (x * MINUTE);
		ast_str_append(&out, 0, "%d minute%s%s ", x, ESS(x),NEEDCOMMA(timeval.tv_sec));
	}
	x = timeval.tv_sec;
	if (x > 0 || ast_str_strlen(out) == 0)
		ast_str_append(&out, 0, "%d second%s ", x, ESS(x));
	ast_cli(fd, "%s: %s\n", prefix, ast_str_buffer(out));
}
