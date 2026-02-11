setup_redirects(struct command *prog, int squirrel[])
{
	int openfd, mode;
	struct redir_struct *redir;

	for (redir = prog->redirects; redir; redir = redir->next) {
		if (redir->rd_type == REDIRECT_HEREDOC2) {

			if (squirrel && redir->rd_fd < 3
			 && squirrel[redir->rd_fd] < 0
			) {
				squirrel[redir->rd_fd] = dup(redir->rd_fd);
			}


			debug_printf_parse("set heredoc '%s'\n",
					redir->rd_filename);
			setup_heredoc(redir);
			continue;
		}

		if (redir->rd_dup == REDIRFD_TO_FILE) {

			char *p;
			if (redir->rd_filename == NULL) {


				bb_error_msg("bug in redirect parse");
				continue;
			}
			mode = redir_table[redir->rd_type].mode;
			p = expand_string_to_string(redir->rd_filename,  1);
			openfd = open_or_warn(p, mode);
			free(p);
			if (openfd < 0) {


				return 1;
			}
		} else {

			openfd = redir->rd_dup;
		}

		if (openfd != redir->rd_fd) {
			if (squirrel && redir->rd_fd < 3
			 && squirrel[redir->rd_fd] < 0
			) {
				squirrel[redir->rd_fd] = dup(redir->rd_fd);
			}
			if (openfd == REDIRFD_CLOSE) {

				close(redir->rd_fd);
			} else {
				xdup2(openfd, redir->rd_fd);
				if (redir->rd_dup == REDIRFD_TO_FILE)
					close(openfd);
			}
		}
	}
	return 0;
}
