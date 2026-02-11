au_do_unlock(const unsigned char dmsg, struct au_mvd_args *a)
{
	if (!a->rename_lock)
		au_unpin(&a->mvd_pin_src);
	else {
		vfsub_unlock_rename(a->mvd_h_src_parent, a->mvd_hdir_src,
				    a->mvd_h_dst_parent, a->mvd_hdir_dst);
		au_pin_hdir_lock(&a->mvd_pin_src);
		au_unpin(&a->mvd_pin_src);
		au_pin_hdir_lock(&a->mvd_pin_dst);
	}
	au_unpin(&a->mvd_pin_dst);
}
