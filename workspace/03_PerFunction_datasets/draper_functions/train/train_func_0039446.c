mono_domain_set (MonoDomain *domain, gboolean force)
{
	if (!force && domain->state == MONO_APPDOMAIN_UNLOADED)
		return FALSE;

	mono_domain_set_internal (domain);

	return TRUE;
}
