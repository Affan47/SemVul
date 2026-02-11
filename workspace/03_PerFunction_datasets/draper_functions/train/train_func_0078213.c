snd_emu10k1_fx8010_info(struct snd_emu10k1 *emu,
				   struct snd_emu10k1_fx8010_info *info)
{
	char **fxbus, **extin, **extout;
	unsigned short fxbus_mask, extin_mask, extout_mask;
	int res;

	info->internal_tram_size = emu->fx8010.itram_size;
	info->external_tram_size = emu->fx8010.etram_pages.bytes / 2;
	fxbus = fxbuses;
	extin = emu->audigy ? audigy_ins : creative_ins;
	extout = emu->audigy ? audigy_outs : creative_outs;
	fxbus_mask = emu->fx8010.fxbus_mask;
	extin_mask = emu->fx8010.extin_mask;
	extout_mask = emu->fx8010.extout_mask;
	for (res = 0; res < 16; res++, fxbus++, extin++, extout++) {
		copy_string(info->fxbus_names[res], fxbus_mask & (1 << res) ? *fxbus : NULL, "FXBUS", res);
		copy_string(info->extin_names[res], extin_mask & (1 << res) ? *extin : NULL, "Unused", res);
		copy_string(info->extout_names[res], extout_mask & (1 << res) ? *extout : NULL, "Unused", res);
	}
	for (res = 16; res < 32; res++, extout++)
		copy_string(info->extout_names[res], extout_mask & (1 << res) ? *extout : NULL, "Unused", res);
	info->gpr_controls = emu->fx8010.gpr_count;
}
