free_server_conf(struct server_conf *server_p)
{
	s_assert(server_p != NULL);
	if(server_p == NULL)
		return;

	if(!EmptyString(server_p->passwd))
	{
		memset(server_p->passwd, 0, strlen(server_p->passwd));
		rb_free(server_p->passwd);
	}

	if(!EmptyString(server_p->spasswd))
	{
		memset(server_p->spasswd, 0, strlen(server_p->spasswd));
		rb_free(server_p->spasswd);
	}

	rb_free(server_p->name);
	rb_free(server_p->host);
	rb_free(server_p->class_name);
	rb_free(server_p);
}
