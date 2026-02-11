lvmcache_vgid_is_cached(const char *vgid) {
	struct lvmcache_vginfo *vginfo;

	if (lvmetad_active())
		return 1;

	vginfo = lvmcache_vginfo_from_vgid(vgid);

	if (!vginfo || !vginfo->vgname)
		return 0;

	if (is_orphan_vg(vginfo->vgname))
		return 0;

	return 1;
}
