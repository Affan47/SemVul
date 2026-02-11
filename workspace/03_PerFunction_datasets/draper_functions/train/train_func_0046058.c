file_apply_children(
    const char *filename,
    file_apply_proc_t function,
    void *userdata)
{
    DIR *dir;
    struct dirent *de;
    estring child;
    int ret = 1;

    if ((dir = opendir(filename)) == 0)
    	return -1;

    while ((de = readdir(dir)) != 0)
    {
    	if (!strcmp(de->d_name, ".") ||
	    !strcmp(de->d_name, ".."))
	    continue;


	child.truncate();
	child.append_string(filename);
	child.append_char('/');
	child.append_string(de->d_name);

	if (!(*function)(child.data(), userdata))
	{
	    ret = 0;
	    break;
	}
    }

    closedir(dir);
    return ret;
}
