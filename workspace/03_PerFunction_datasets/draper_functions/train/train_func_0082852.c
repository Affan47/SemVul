buspirate_powerup(struct programmer_t *pgm)
{
	if (pgm->flag & BP_FLAG_IN_BINMODE) {

		return;
	} else {
		if (buspirate_expect(pgm, "W\n", "Power supplies ON", 1)) {
			if (pgm->flag & BP_FLAG_XPARM_CPUFREQ) {
				char buf[25];
				int ok = 0;
				snprintf(buf, sizeof(buf), "%d\n", PDATA(pgm)->cpufreq);
				if (buspirate_expect(pgm, "g\n", "Frequency in KHz", 1)) {
					if (buspirate_expect(pgm, buf, "Duty cycle in %", 1)) {
						if (buspirate_expect(pgm, "50\n", "PWM active", 1)) {
							ok = 1;
						}
					}
				}
				if(!ok) {
					fprintf(stderr, "%s: warning: did not get a response to start PWM command.\n", progname);
				}
			}
			return;
		}
	}

	fprintf(stderr, "%s: warning: did not get a response to PowerUp command.\n", progname);
	fprintf(stderr, "%s: warning: Trying to continue anyway...\n", progname);
}
