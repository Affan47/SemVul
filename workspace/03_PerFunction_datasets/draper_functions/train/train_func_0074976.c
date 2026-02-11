wl12xx_top_reg_write(struct wl1271 *wl, int addr,
					     u16 val)
{
	int ret;


	addr = (addr >> 1) + 0x30000;
	ret = wlcore_write32(wl, WL12XX_OCP_POR_CTR, addr);
	if (ret < 0)
		goto out;


	ret = wlcore_write32(wl, WL12XX_OCP_DATA_WRITE, val);
	if (ret < 0)
		goto out;


	ret = wlcore_write32(wl, WL12XX_OCP_CMD, OCP_CMD_WRITE);
	if (ret < 0)
		goto out;

out:
	return ret;
}
