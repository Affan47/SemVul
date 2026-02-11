fill_tgt_context(char *subsys, char *id,
			    struct boot_context *context)
{
	int rc;

	rc = sysfs_get_str(id, subsys, "target-name", context->targetname,
			   sizeof(context->targetname));
	if (rc)
		return rc;

	rc = sysfs_get_str(id, subsys, "ip-addr", context->target_ipaddr,
			   sizeof(context->target_ipaddr));
	if (rc)
		return rc;


	if (sysfs_get_int(id, subsys, "port", &context->target_port))
		context->target_port = ISCSI_LISTEN_PORT;

	sysfs_get_str(id, subsys, "lun", context->lun,
		      sizeof(context->lun));
	sysfs_get_str(id, subsys, "chap-name", context->chap_name,
		      sizeof(context->chap_name));
	sysfs_get_str(id, subsys, "chap-secret", context->chap_password,
		      sizeof(context->chap_password));
	sysfs_get_str(id, subsys, "rev-chap-name", context->chap_name_in,
		      sizeof(context->chap_name_in));
	sysfs_get_str(id, subsys, "rev-chap-name-secret",
		      context->chap_password_in,
		      sizeof(context->chap_password_in));
	return 0;
}
