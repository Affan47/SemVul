destroy_parameters(struct cgi_parameters *cp)
{
	int i;

	if (cp->cgi_envp) {
		for (i = 0; i < cp->cgi_envc; i++)
			if (cp->cgi_envp[i])
				free(cp->cgi_envp[i]);
		free(cp->cgi_envp);
	}
	if (cp->cgi_argv) {
		for (i = 0; i < cp->cgi_argc; i++)
			if (cp->cgi_argv[i])
				free(cp->cgi_argv[i]);
		free(cp->cgi_argv);
	}
}
