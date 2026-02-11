gvplugin_package_record(GVC_t * gvc, char *path, char *name)
{
    gvplugin_package_t *package = gmalloc(sizeof(gvplugin_package_t));
    package->path = (path) ? strdup(path) : NULL;
    package->name = strdup(name);
    package->next = gvc->packages;
    gvc->packages = package;
    return package;
}
