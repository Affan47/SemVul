read_file_ani(struct file *file, char __user *user_buf,
			     size_t count, loff_t *ppos)
{
	struct ath_softc *sc = file->private_data;
	struct ath_common *common = ath9k_hw_common(sc->sc_ah);
	struct ath_hw *ah = sc->sc_ah;
	unsigned int len = 0;
	const unsigned int size = 1024;
	ssize_t retval = 0;
	char *buf;
	int i;
	struct {
		const char *name;
		unsigned int val;
	} ani_info[] = {
		{ "ANI RESET", ah->stats.ast_ani_reset },
		{ "OFDM LEVEL", ah->ani.ofdmNoiseImmunityLevel },
		{ "CCK LEVEL", ah->ani.cckNoiseImmunityLevel },
		{ "SPUR UP", ah->stats.ast_ani_spurup },
		{ "SPUR DOWN", ah->stats.ast_ani_spurup },
		{ "OFDM WS-DET ON", ah->stats.ast_ani_ofdmon },
		{ "OFDM WS-DET OFF", ah->stats.ast_ani_ofdmoff },
		{ "MRC-CCK ON", ah->stats.ast_ani_ccklow },
		{ "MRC-CCK OFF", ah->stats.ast_ani_cckhigh },
		{ "FIR-STEP UP", ah->stats.ast_ani_stepup },
		{ "FIR-STEP DOWN", ah->stats.ast_ani_stepdown },
		{ "INV LISTENTIME", ah->stats.ast_ani_lneg_or_lzero },
		{ "OFDM ERRORS", ah->stats.ast_ani_ofdmerrs },
		{ "CCK ERRORS", ah->stats.ast_ani_cckerrs },
	};

	buf = kzalloc(size, GFP_KERNEL);
	if (buf == NULL)
		return -ENOMEM;

	len += scnprintf(buf + len, size - len, "%15s: %s\n", "ANI",
			 common->disable_ani ? "DISABLED" : "ENABLED");

	if (common->disable_ani)
		goto exit;

	for (i = 0; i < ARRAY_SIZE(ani_info); i++)
		len += scnprintf(buf + len, size - len, "%15s: %u\n",
				 ani_info[i].name, ani_info[i].val);

exit:
	if (len > size)
		len = size;

	retval = simple_read_from_buffer(user_buf, count, ppos, buf, len);
	kfree(buf);

	return retval;
}
