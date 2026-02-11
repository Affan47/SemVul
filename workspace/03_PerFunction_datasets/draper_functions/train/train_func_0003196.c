check_cvs_version(int req_major, int req_minor, int req_extra)
{
    if (!client_version[0])
    {
	if (cvs_direct_ctx)
	    cvs_version(cvs_direct_ctx, client_version, server_version);
	else
	    get_version_external();
    }

    return (check_version_string(client_version, req_major, req_minor, req_extra) &&
	    (!server_version[0] || check_version_string(server_version, req_major, req_minor, req_extra)));
}
