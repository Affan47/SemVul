ext_phys_paylen(const extvec_t *e)
{
	extdesc_t *d = e->opaque;

	g_assert(e->opaque != NULL);

	return d->ext_phys_paylen;
}
