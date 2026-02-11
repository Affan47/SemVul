cgit_log_link(char *name, char *title, char *class, char *head,
		   char *rev, char *path, int ofs, char *grep, char *pattern,
		   int showmsg)
{
	char *delim;

	delim = repolink(title, class, "log", head, path);
	if (rev && strcmp(rev, ctx.qry.head)) {
		html(delim);
		html("id=");
		html_url_arg(rev);
		delim = "&";
	}
	if (grep && pattern) {
		html(delim);
		html("qt=");
		html_url_arg(grep);
		delim = "&";
		html(delim);
		html("q=");
		html_url_arg(pattern);
	}
	if (ofs > 0) {
		html(delim);
		html("ofs=");
		htmlf("%d", ofs);
		delim = "&";
	}
	if (showmsg) {
		html(delim);
		html("showmsg=1");
	}
	html("'>");
	html_txt(name);
	html("</a>");
}
