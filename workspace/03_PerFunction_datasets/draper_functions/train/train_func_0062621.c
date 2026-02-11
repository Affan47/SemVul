get_anon_system_at_depth (int fd)
{
    equation_system *sys;
    GList *tmp = sysstack;

    while (tmp != NULL) {
	sys = tmp->data;
	if (sys->fd == fd) {
	    return sys;
	}
	tmp = tmp->next;
    }

    return NULL;
}
