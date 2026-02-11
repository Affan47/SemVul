wl18xx_get_pg_ver(struct wl1271 *wl, s8 *ver)
{
	u32 fuse;
	s8 rom = 0, metal = 0, pg_ver = 0, rdl_ver = 0, package_type = 0;
	int ret;

	ret = wlcore_set_partition(wl, &wl->ptable[PART_TOP_PRCM_ELP_SOC]);
	if (ret < 0)
		goto out;

	ret = wlcore_read32(wl, WL18XX_REG_FUSE_DATA_2_3, &fuse);
	if (ret < 0)
		goto out;

	package_type = (fuse >> WL18XX_PACKAGE_TYPE_OFFSET) & 1;

	ret = wlcore_read32(wl, WL18XX_REG_FUSE_DATA_1_3, &fuse);
	if (ret < 0)
		goto out;

	pg_ver = (fuse & WL18XX_PG_VER_MASK) >> WL18XX_PG_VER_OFFSET;
	rom = (fuse & WL18XX_ROM_VER_MASK) >> WL18XX_ROM_VER_OFFSET;

	if ((rom <= 0xE) && (package_type == WL18XX_PACKAGE_TYPE_WSP))
		metal = (fuse & WL18XX_METAL_VER_MASK) >>
			WL18XX_METAL_VER_OFFSET;
	else
		metal = (fuse & WL18XX_NEW_METAL_VER_MASK) >>
			WL18XX_NEW_METAL_VER_OFFSET;

	ret = wlcore_read32(wl, WL18XX_REG_FUSE_DATA_2_3, &fuse);
	if (ret < 0)
		goto out;

	rdl_ver = (fuse & WL18XX_RDL_VER_MASK) >> WL18XX_RDL_VER_OFFSET;

	wl1271_info("wl18xx HW: %s, PG %d.%d (ROM 0x%x)",
		    wl18xx_rdl_name(rdl_ver), pg_ver, metal, rom);

	if (ver)
		*ver = pg_ver;

	ret = wlcore_set_partition(wl, &wl->ptable[PART_BOOT]);

out:
	return ret;
}
