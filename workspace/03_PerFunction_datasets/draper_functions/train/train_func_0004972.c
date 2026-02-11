ntfs_attr_can_be_non_resident(const ntfs_volume *vol, const ATTR_TYPE type)
{
	ATTR_DEF *ad;


	ad = ntfs_attr_find_in_attrdef(vol, type);
	if (unlikely(!ad))
		return -ENOENT;

	if (ad->flags & ATTR_DEF_RESIDENT)
		return -EPERM;
	return 0;
}
