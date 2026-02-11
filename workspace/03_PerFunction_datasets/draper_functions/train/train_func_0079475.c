bt_announce(options_t *o, char* announce_url, unsigned unused)
{
	(void)unused;

	if (!announce_url || !announce_url[0]) return;
	if (!o->bt_announce) o->bt_announce = rsh_vector_new_simple();
	rsh_vector_add_ptr(o->bt_announce, rsh_strdup(announce_url));
}
