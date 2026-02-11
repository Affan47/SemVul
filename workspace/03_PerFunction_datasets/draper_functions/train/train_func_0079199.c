tomoyo_initerface_init(void)
{
	struct dentry *tomoyo_dir;


	if (current_cred()->security != &tomoyo_kernel_domain)
		return 0;

	tomoyo_dir = securityfs_create_dir("tomoyo", NULL);
	tomoyo_create_entry("query",            0600, tomoyo_dir,
			    TOMOYO_QUERY);
	tomoyo_create_entry("domain_policy",    0600, tomoyo_dir,
			    TOMOYO_DOMAINPOLICY);
	tomoyo_create_entry("exception_policy", 0600, tomoyo_dir,
			    TOMOYO_EXCEPTIONPOLICY);
	tomoyo_create_entry("audit",            0400, tomoyo_dir,
			    TOMOYO_AUDIT);
	tomoyo_create_entry(".process_status",  0600, tomoyo_dir,
			    TOMOYO_PROCESS_STATUS);
	tomoyo_create_entry("stat",             0644, tomoyo_dir,
			    TOMOYO_STAT);
	tomoyo_create_entry("profile",          0600, tomoyo_dir,
			    TOMOYO_PROFILE);
	tomoyo_create_entry("manager",          0600, tomoyo_dir,
			    TOMOYO_MANAGER);
	tomoyo_create_entry("version",          0400, tomoyo_dir,
			    TOMOYO_VERSION);
	securityfs_create_file("self_domain", 0666, tomoyo_dir, NULL,
			       &tomoyo_self_operations);
	tomoyo_load_builtin_policy();
	return 0;
}
