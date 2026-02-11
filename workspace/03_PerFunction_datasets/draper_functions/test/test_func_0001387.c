permissions_set(char *name, uid_t uid, gid_t gid, mode_t mode, mode_t mask)
{
	mode_t realmode = (mode & ~mask);

	log(L_DEBUG, "Setting \"%s\" to %d.%d (%04o)...\n", name, uid, gid, realmode);

	if (chown(name, uid, gid) == -1)
	{
		log(L_ERROR, "Can't set owner of \"%s\" (%s).\n", name, strerror(errno));

		returnerror();
	}

	if (chmod(name, realmode) == -1)
	{
		log(L_ERROR, "Can't set mode of \"%s\" (%s).\n", name, strerror(errno));

		returnerror();
	}

	returnok();
}
