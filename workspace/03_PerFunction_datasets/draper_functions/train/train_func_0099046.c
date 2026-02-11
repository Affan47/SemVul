listscripts(const char **restrict script, const char mode, const ushort lvl)
{
    static list_t * tmp;
    service_t * serv;
    ushort level;
    dir_t * dir;

    if (!*script)
	tmp  = d_start->next;

    do {
	serv = (service_t*)0;
	if (tmp == d_start)
	    break;
	prefetch(tmp->next);
	dir = getdir(tmp);

        attof(dir)->korder = dir->stopp.deep;
        attof(dir)->sorder = dir->start.deep;

	serv = dir->serv;
	*script = serv->attr.script;

	switch (mode) {
	case 'X':
	    level = (dir->stopp.run.lvl|dir->start.run.lvl);
	    break;
	case 'K':
	    level = dir->stopp.run.lvl;
	    break;
	default:
	    level = dir->start.run.lvl;
	    break;
	}

	tmp = tmp->next;

    } while ((*script == (char*)0) || (level & lvl) == 0);

    return serv;
}
