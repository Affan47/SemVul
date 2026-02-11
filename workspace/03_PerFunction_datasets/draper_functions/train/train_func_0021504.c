csg_write_controls()
{
	int idx;

	startSection(Section::Controls);

	cfwrite_ushort(CCFG_MAX, cfp);

	for (idx = 0; idx < CCFG_MAX; idx++) {
		cfwrite_short(Control_config[idx].key_id, cfp);
		cfwrite_short(Control_config[idx].joy_id, cfp);

		cfwrite_short(-1, cfp);
	}

	endSection();
}
