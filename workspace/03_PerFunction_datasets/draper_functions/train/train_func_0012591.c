info_major_minor_in_range (MonoAssemblyBindingInfo *info, MonoAssemblyName *aname)
{
	if (!info->has_old_version_bottom)
		return FALSE;

	if (info->old_version_bottom.major > aname->major || info->old_version_bottom.minor > aname->minor)
		return FALSE;

	if (info->has_old_version_top && (info->old_version_top.major < aname->major || info->old_version_top.minor < aname->minor))
		return FALSE;


	info->major = aname->major;
	info->minor = aname->minor;

	return TRUE;
}
