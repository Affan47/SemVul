G__tempfile(int pid)
{
    char path[GPATH_MAX];
    char name[GNAME_MAX];
    char element[100];
    static int uniq = 0;
    struct stat st;

    if (pid <= 0)
	pid = getpid();
    G__temp_element(element);
    do {
	sprintf(name, "%d.%d", pid, uniq++);
	G__file_name(path, element, name, G_mapset());
    }
    while (stat(path, &st) == 0);

    return G_store(path);
}
