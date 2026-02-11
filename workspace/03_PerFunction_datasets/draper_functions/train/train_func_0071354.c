show_procinfo_msg(ProcInfo *p)
{
	if ((p != NULL) && (lcd_wid > 0) && (lcd_hgt > 0)) {
		if (p->endtime > 0) {

			if ((p->shown) || (!p->feedback))
				return 1;

			sock_printf(sock, "screen_add [%u]\n", p->pid);
			sock_printf(sock, "screen_set [%u] -name {lcdexec [%u]}"
					  " -priority alert -timeout %d"
					  " -heartbeat off\n",
					p->pid, p->pid, 6*8);

			if (lcd_hgt > 2) {
				sock_printf(sock, "widget_add [%u] t title\n", p->pid);
				sock_printf(sock, "widget_set [%u] t {%s}\n", p->pid, p->cmd->displayname);
				sock_printf(sock, "widget_add [%u] s1 string\n", p->pid);
				sock_printf(sock, "widget_add [%u] s2 string\n", p->pid);
				sock_printf(sock, "widget_add [%u] s3 string\n", p->pid);

				sock_printf(sock, "widget_set [%u] s1 1 2 {[%u] finished%s}\n",
						p->pid, p->pid, (WIFSIGNALED(p->status) ? "," : ""));

				if (WIFEXITED(p->status)) {
					if (WEXITSTATUS(p->status) == EXIT_SUCCESS) {
						sock_printf(sock, "widget_set [%u] s2 1 3 {successfully.}\n",
								p->pid);
					}
					else {
						sock_printf(sock, "widget_set [%u] s2 1 3 {with code 0x%02X.}\n",
								p->pid, WEXITSTATUS(p->status));
					}
				}
				else if (WIFSIGNALED(p->status)) {
					sock_printf(sock, "widget_set [%u] s2 1 3 {killed by SIG %d.}\n",
						p->pid, WTERMSIG(p->status));
				}

				if (lcd_hgt > 3)
					sock_printf(sock, "widget_set [%u] s3 1 4 {Exec time: %lds}\n",
							p->pid, p->endtime - p->starttime);
			}
			else {
				sock_printf(sock, "widget_add [%u] s1 string\n", p->pid);
				sock_printf(sock, "widget_add [%u] s2 string\n", p->pid);
				sock_printf(sock, "widget_set [%u] s1 1 1 {%s}\n",
						p->pid, p->cmd->displayname);
				if (WIFEXITED(p->status)) {
					if (WEXITSTATUS(p->status) == EXIT_SUCCESS) {
						sock_printf(sock, "widget_set [%u] s2 1 2 {succeeded}\n",
								p->pid, p->status);
					}
					else {
						sock_printf(sock, "widget_set [%u] s2 1 2 {finished (0x%02X)}\n",
								p->pid, p->status);
					}
				}
				else if (WIFSIGNALED(p->status)) {
					sock_printf(sock, "widget_set [%u] s2 1 2 {killed by SIG %d}\n",
							p->pid, WTERMSIG(p->status));

				}
			}
			return 1;
		}
	}
	return 0;
}
