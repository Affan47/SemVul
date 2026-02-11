dcb_gpio_entry(struct nvkm_bios *bios, int idx, int ent, u8 *ver, u8 *len)
{
	u8  hdr, cnt, xver;
	u16 gpio;

	if (!idx--)
		gpio = dcb_gpio_table(bios, ver, &hdr, &cnt, len);
	else
		gpio = dcb_xpio_table(bios, idx, &xver, &hdr, &cnt, len);

	if (gpio && ent < cnt)
		return gpio + hdr + (ent * *len);

	return 0x0000;
}
