vdi_random_healthy(const struct director *d, const struct sess *sp)
{
	struct vdi_random *vs;
	int i;

	CHECK_OBJ_NOTNULL(d, DIRECTOR_MAGIC);
	CAST_OBJ_NOTNULL(vs, d->priv, VDI_RANDOM_MAGIC);

	for (i = 0; i < vs->nhosts; i++) {
		if (VDI_Healthy(vs->hosts[i].backend, sp))
			return (1);
	}
	return (0);
}
