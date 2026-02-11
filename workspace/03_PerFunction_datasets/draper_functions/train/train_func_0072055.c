socket_httpd_page(struct httpd_session_data* sd, const char* url)
{
	int i, len;
	char *p;

	static const struct {
		const char *mode;
		void (*func)(struct httpd_session_data*, const char*);
	} pages[] = {
		{ "dosattack",  socket_httpd_page_dos_attack      },
		{ "access",     socket_httpd_page_access_settings },
		{ "connection", socket_httpd_page_connection      },
	};

	if (socket_ctrl_panel_httpd == 0) {
		httpd_send(sd, 403, "text/plain", 9, "Forbidden");
		return;
	}

	p = httpd_get_value(sd, "mode");
	for(i = 0; i < sizeof(pages) / sizeof(pages[0]); i++) {
		if (strcmp(p, pages[i].mode) == 0) {
			aFree(p);
			pages[i].func(sd, url);
			return;
		}
	}
	aFree(p);

	socket_httpd_page_header(sd);

	len = sprintf(WFIFOP(sd->fd, 0),
	      "<ul>\n"
	      "<li><a href=\"%s?mode=access\">View Access Control Settings</a>\n"
	      "<li><a href=\"%s?mode=dosattack\">Anti-DoS Attack Status</a>\n"
	      "<li><a href=\"%s?mode=connection\">Connection Status</a>\n"
	      "</ul>\n", socket_ctrl_panel_url, socket_ctrl_panel_url, socket_ctrl_panel_url);
	WFIFOSET(sd->fd, len);

	socket_httpd_page_footer(sd->fd);

	return;
}
