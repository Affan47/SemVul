idl_release_private(struct attrinfo *a)
{
	if (idl_new) {
		return idl_new_release_private(a);
	} else {
		return idl_old_release_private(a);
	}
}
