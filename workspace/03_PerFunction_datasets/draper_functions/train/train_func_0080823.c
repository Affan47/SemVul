check_directory(krb5_context context,
		const char *dirname,
		const char *owner,
	        krb5_boolean is_system_location,
		krb5_const_principal principal,
		krb5_boolean *result)
{
    DIR *d;
    struct dirent *dent;
    char filename[MAXPATHLEN];
    size_t len;
    krb5_error_code ret = 0;
    struct stat st;

    *result = FALSE;

    if (lstat(dirname, &st) < 0)
	return errno;

    if (!S_ISDIR(st.st_mode)) {
	krb5_set_error_message(context, ENOTDIR, "k5login.d not a directory");
	return ENOTDIR;
    }

    if ((d = opendir(dirname)) == NULL) {
	krb5_set_error_message(context, ENOTDIR, "Could not open k5login.d");
	return errno;
    }

    ret = check_owner_dir(context, dirname, is_system_location, d, &st, owner);
    if (ret)
	goto out;

    while ((dent = readdir(d)) != NULL) {


	if (strcmp(dent->d_name, ".") == 0 ||
	   strcmp(dent->d_name, "..") == 0 ||
	   dent->d_name[0] == '#' ||
	   dent->d_name[strlen(dent->d_name) - 1] == '~')
	    continue;
	len = snprintf(filename, sizeof(filename), "%s/%s", dirname, dent->d_name);

	if (len < sizeof(filename)) {
	    ret = check_one_file(context, filename, owner, is_system_location,
				 principal, result);
	    if (ret == 0 && *result == TRUE)
		break;
	}
	ret = 0;
    }

out:
    closedir(d);
    return ret;
}
