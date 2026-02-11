file_path_changed(property_t prop)
{
    char *pathname;

	tilda_expand(prop);
	pathname = gnet_prop_get_string(prop, NULL, 0);
	request_directory(pathname);
    G_FREE_NULL(pathname);
    return FALSE;
}
