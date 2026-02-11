wrap_passphrase_if_necessary(const char *username, uid_t uid, char *wrapped_pw_filename, char *passphrase, char *salt)
{
	char *unwrapped_pw_filename = NULL;
	struct stat s;
	int rc = 0;

	rc = asprintf(&unwrapped_pw_filename, "/dev/shm/.ecryptfs-%s", username);
	if (rc == -1) {
		syslog(LOG_ERR, "pam_ecryptfs: Unable to allocate memory\n");
		return -ENOMEM;
	}


	if (stat(unwrapped_pw_filename, &s) == 0 && (s.st_uid == uid) &&
	    stat(wrapped_pw_filename, &s) != 0  &&
	    passphrase != NULL && *passphrase != '\0' &&
	    username != NULL && *username != '\0') {
		setuid(uid);
		rc = ecryptfs_wrap_passphrase_file(wrapped_pw_filename, passphrase, salt, unwrapped_pw_filename);
		if (rc != 0) {
			syslog(LOG_ERR, "pam_ecryptfs: Error wrapping cleartext password; " "rc = [%d]\n", rc);
		}
		return rc;
	}
	return 0;
}
