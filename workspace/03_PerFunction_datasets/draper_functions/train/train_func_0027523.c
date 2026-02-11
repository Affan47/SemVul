aa_profile_af_perm(struct aa_profile *profile, struct common_audit_data *sa,
		       u32 request, u16 family, int type)
{
	struct aa_perms perms = { };

	AA_BUG(family >= AF_MAX);
	AA_BUG(type < 0 && type >= SOCK_MAX);

	if (profile_unconfined(profile))
		return 0;

	perms.allow = (profile->net.allow[family] & (1 << type)) ?
		ALL_PERMS_MASK : 0;
	perms.audit = (profile->net.audit[family] & (1 << type)) ?
		ALL_PERMS_MASK : 0;
	perms.quiet = (profile->net.quiet[family] & (1 << type)) ?
		ALL_PERMS_MASK : 0;
	aa_apply_modes_to_perms(profile, &perms);

	return aa_check_perms(profile, &perms, request, sa, audit_net_cb);
}
