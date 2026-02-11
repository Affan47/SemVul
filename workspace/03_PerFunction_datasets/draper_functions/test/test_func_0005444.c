dirSetup(void)
{
    for (u_int i = 0, n = N(dirs); i < n; i++) {
	struct stat sb;
	if (!FileCache::lookup(dirs[i].pathname, sb) || !S_ISDIR(sb.st_mode)) {
	    logError("%s: Not a directory.", dirs[i].pathname);
	    continue;
	}
	dirs[i].ino = sb.st_ino;
	if (streq(dirs[i].pathname, "/"))
	    cwd = &dirs[i];
    }
}
