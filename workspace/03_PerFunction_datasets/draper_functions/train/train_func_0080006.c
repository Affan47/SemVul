get_service_info(char *name, std::string &cmd, int &maxcon, int &curcon, uid_t &uid, gid_t &gid)
{

    std::list<serviceinfo>::iterator sii;
    sii = find(servicelist.begin(), servicelist.end(), name);
    if (sii != servicelist.end())
    {
	cmd = sii->get_command();
	maxcon = sii->get_max_connections();
	curcon = sii->get_cur_connections();
	uid = sii->get_uid();
	gid = sii->get_gid();

	return 0;
    }

    return -1;
}
