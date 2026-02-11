check_pseudoelement(int which, bool isoutput, const char *name, ErrorHandler *errh) const
{
    Bitvector used(_element_nports[1-isoutput][which]);
    for (const Connection *it = _conn.begin(); it != _conn.end(); ++it)
	if ((*it)[1-isoutput].idx == which)
	    used[(*it)[1-isoutput].port] = true;
    if (_element_nports[isoutput][which])
	errh->error("%<%s%> pseudoelement %<%s%> may only be used as %s", name, port_names[isoutput], port_names[1-isoutput]);
    for (int i = 0; i < used.size(); i++)
	if (!used[i])
	    errh->error("%<%s%> %s %d missing", name, port_names[isoutput], i);
    return used.size();
}
