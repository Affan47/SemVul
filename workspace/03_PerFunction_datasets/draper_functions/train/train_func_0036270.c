mls_export_netlbl_lvl(struct context *context,
			   struct netlbl_lsm_secattr *secattr)
{
	if (!policydb.mls_enabled)
		return;

	secattr->attr.mls.lvl = context->range.level[0].sens - 1;
	secattr->flags |= NETLBL_SECATTR_MLS_LVL;
}
