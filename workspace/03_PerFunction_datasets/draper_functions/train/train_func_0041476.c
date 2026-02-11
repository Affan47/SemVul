auth_unix_accept(struct link *link, char **subject, time_t stoptime)
{
	char path[AUTH_LINE_MAX];
	char line[AUTH_LINE_MAX];
	int success = 0;
	struct stat buf;
	struct passwd *p;

	debug(D_AUTH, "unix: generating challenge");
	make_challenge_path(path);
	link_putfstring(link, "%s\n", stoptime, path);

	debug(D_AUTH, "unix: waiting for response");
	if(link_readline(link, line, sizeof(line), stoptime)) {
		if(!strcmp(line, "yes")) {
			int file_exists = 0;
			int i=0;

			for(i=0;i<challenge_timeout;i++) {


				DIR *d = opendir(challenge_dir);
				if(d) {
				    closedir(d);
				}

				if(stat(path,&buf)==0) {
					file_exists = 1;
					break;
				} else {
					debug(D_AUTH,"unix: client claims success, but I don't see it yet...");
					sleep(1);
				}
			}

			if(file_exists) {
				debug(D_AUTH, "unix: got response");
				debug(D_AUTH, "unix: client is uid %d", buf.st_uid);
				p = auth_get_passwd_from_uid(buf.st_uid);
				if(p) {
					debug(D_AUTH, "unix: client is subject %s", p->pw_name);
					link_putliteral(link, "yes\n", stoptime);
					*subject = xxstrdup(p->pw_name);
					success = 1;
				} else {
					debug(D_AUTH, "unix: there is no user corresponding to uid %d", buf.st_uid);
					link_putliteral(link, "no\n", stoptime);
				}
			} else {
				debug(D_AUTH, "unix: client failed the challenge: %s", strerror(errno));
				link_putliteral(link, "no\n", stoptime);
			}
		} else {
			debug(D_AUTH, "unix: client declined the challenge");
		}
	}

	unlink(path);

	return success;
}
