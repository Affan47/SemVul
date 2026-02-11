buspirate_powerdown(struct programmer_t *pgm)
{
	if (pgm->flag & BP_FLAG_IN_BINMODE) {


		if (buspirate_expect_bin_byte(pgm, 0x40, 0x01))
			return;
	} else {
		if (pgm->flag & BP_FLAG_XPARM_CPUFREQ) {
			if (!buspirate_expect(pgm, "g\n", "PWM disabled", 1)) {
				fprintf(stderr, "%s: warning: did not get a response to stop PWM command.\n", progname);
			}
		}
		if (buspirate_expect(pgm, "w\n", "Power supplies OFF", 1))
			return;
	}

	fprintf(stderr, "%s: warning: did not get a response to PowerDown command.\n", progname);
}
