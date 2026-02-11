klp_is_patch_registered(struct klp_patch *patch)
{
	struct klp_patch *mypatch;

	list_for_each_entry(mypatch, &klp_patches, list)
		if (mypatch == patch)
			return true;

	return false;
}
