cdrom_modeset (uae_u8 *cmd)
{
	cdtv_sectorsize = (cmd[2] << 8) | cmd[3];
	if (cdtv_sectorsize != 2048 && cdtv_sectorsize != 2336 && cdtv_sectorsize != 2352 && cdtv_sectorsize != 2328) {
		write_log (_T("CDTV: tried to set unknown sector size %d\n"), cdtv_sectorsize);
		cdtv_sectorsize = 2048;
	}
	return 0;
}
