pv_fmt_dup(const struct physical_volume *pv)
{
	if (!pv->fmt)
		return NULL;
	return dm_pool_strdup(pv->vg->vgmem, pv->fmt->name);
}
