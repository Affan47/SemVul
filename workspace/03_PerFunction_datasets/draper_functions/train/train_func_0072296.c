_text_vg_setup(struct format_instance *fid __attribute__((unused)),
			  struct volume_group *vg)
{
	if (vg->extent_size & (vg->extent_size - 1)) {
		log_error("Extent size must be power of 2");
		return 0;
	}

	return 1;
}
