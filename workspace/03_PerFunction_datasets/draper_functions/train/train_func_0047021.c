show_line(struct grep_opt *opt, char *bol, char *eol,
		      const char *name, unsigned lno, char sign)
{
	int rest = eol - bol;
	char sign_str[1];

	sign_str[0] = sign;
	if (opt->pre_context || opt->post_context) {
		if (opt->last_shown == 0) {
			if (opt->show_hunk_mark)
				opt->output(opt, "--\n", 3);
			else
				opt->show_hunk_mark = 1;
		} else if (lno > opt->last_shown + 1)
			opt->output(opt, "--\n", 3);
	}
	opt->last_shown = lno;

	if (opt->null_following_name)
		sign_str[0] = '\0';
	if (opt->pathname) {
		opt->output(opt, name, strlen(name));
		opt->output(opt, sign_str, 1);
	}
	if (opt->linenum) {
		char buf[32];
		snprintf(buf, sizeof(buf), "%d", lno);
		opt->output(opt, buf, strlen(buf));
		opt->output(opt, sign_str, 1);
	}
	if (opt->color) {
		regmatch_t match;
		enum grep_context ctx = GREP_CONTEXT_BODY;
		int ch = *eol;
		int eflags = 0;

		*eol = '\0';
		while (next_match(opt, bol, eol, ctx, &match, eflags)) {
			if (match.rm_so == match.rm_eo)
				break;

			opt->output(opt, bol, match.rm_so);
			opt->output(opt, opt->color_match,
				    strlen(opt->color_match));
			opt->output(opt, bol + match.rm_so,
				    (int)(match.rm_eo - match.rm_so));
			opt->output(opt, GIT_COLOR_RESET,
				    strlen(GIT_COLOR_RESET));
			bol += match.rm_eo;
			rest -= match.rm_eo;
			eflags = REG_NOTBOL;
		}
		*eol = ch;
	}
	opt->output(opt, bol, rest);
	opt->output(opt, "\n", 1);
}
