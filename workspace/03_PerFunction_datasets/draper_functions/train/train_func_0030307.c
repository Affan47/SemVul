gf_term_post_connect_object(GF_Terminal *term, GF_ObjectManager *odm, char *serviceURL, char *parent_url)
{
	GF_TermConnectObject *connect;
	GF_SAFEALLOC(connect, GF_TermConnectObject);
	connect->odm = odm;
	connect->service_url = gf_strdup(serviceURL);
	connect->parent_url = parent_url ? gf_strdup(parent_url) : NULL;

	gf_term_lock_media_queue(term, 1);
	gf_list_add(term->connection_tasks, connect);
	gf_term_lock_media_queue(term, 0);
}
