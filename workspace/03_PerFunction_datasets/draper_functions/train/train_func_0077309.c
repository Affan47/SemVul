list_acl(char *file)
{
	acl_t acl = NULL;
	acl_t dacl = NULL;
	char *acl_text, *dacl_text = NULL;

	if ((acl = acl_get_file(file, ACL_TYPE_ACCESS)) == NULL) {
		fprintf(stderr, _("%s: cannot get access ACL on '%s': %s\n"),
			program, file, strerror(errno));
		return 0;
	}
	if ((dacl = acl_get_file(file, ACL_TYPE_DEFAULT)) == NULL &&
	    (errno != EACCES)) {
		fprintf(stderr, _("%s: cannot get default ACL on '%s': %s\n"),
			program, file, strerror(errno));
		return 0;
	}
	acl_text = acl_to_any_text(acl, NULL, ',', TEXT_ABBREVIATE);
	if (acl_text == NULL) {
		fprintf(stderr, _("%s: cannot get access ACL text on "
			"'%s': %s\n"), program, file, strerror(errno));
		return 0;
	}
	if (acl_entries(dacl) > 0) {
		dacl_text = acl_to_any_text(dacl, NULL, ',', TEXT_ABBREVIATE);
		if (dacl_text == NULL) {
			fprintf(stderr, _("%s: cannot get default ACL text on "
				"'%s': %s\n"), program, file, strerror(errno));
			return 0;
		}
	}
	if (dacl_text) {
		printf("%s [%s/%s]\n", file, acl_text, dacl_text);
		acl_free(dacl_text);
	} else
		printf("%s [%s]\n", file, acl_text);
	acl_free(acl_text);
	acl_free(acl);
	acl_free(dacl);
	return 1;
}
