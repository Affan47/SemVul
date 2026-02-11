save_action_replay (int *len, uae_u8 *dstptr)
{
	uae_u8 *dstbak, *dst;

	if (!armemory_ram || !armemory_rom || !armodel)
		return 0;
	if (dstptr)
		dstbak = dst = dstptr;
	else
		dstbak = dst = xmalloc (uae_u8, arram_size + sizeof ar_custom + sizeof ar_ciaa + sizeof ar_ciab + 1024);
	save_u8 (0);
	save_u8 (armodel);
	save_u32 (get_crc32 (armemory_rom + 4, arrom_size - 4));
	save_string (currprefs.cartfile);
	save_u32 (arrom_size);
	save_u32 (arram_size);
	memcpy (dst, armemory_ram, arram_size);
	dst += arram_size;
	save_u32 (sizeof ar_custom);
	memcpy (dst, ar_custom, sizeof ar_custom);
	dst += sizeof ar_custom;
	save_u32 (sizeof ar_ciaa);
	memcpy (dst, ar_ciaa, sizeof ar_ciaa);
	dst += sizeof ar_ciaa;
	save_u32 (sizeof ar_ciab);
	memcpy (dst, ar_ciab, sizeof ar_ciab);
	dst += sizeof ar_ciab;
	*len = dst - dstbak;
	return dstbak;
}
