wifi_utils_is_wifi (const char *iface, const char *sysfs_path)
{
	char phy80211_path[255];
	struct stat s;

	g_return_val_if_fail (iface != NULL, FALSE);

	if (sysfs_path) {

		snprintf (phy80211_path, sizeof (phy80211_path), "%s/phy80211", sysfs_path);
		if ((stat (phy80211_path, &s) == 0 && (s.st_mode & S_IFDIR)))
			return TRUE;
	}

	if (wifi_nl80211_is_wifi (iface))
		return TRUE;

#if HAVE_WEXT
	if (wifi_wext_is_wifi (iface))
		return TRUE;
#endif

	return FALSE;
}
