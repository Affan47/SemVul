suggest_hpet(void)
{
	FILE *file;
	char buffer[1024];
	file = fopen("/sys/devices/system/clocksource/clocksource0/available_clocksource", "r");
	if (!file)
		return;
	memset(buffer, 0, 1024);

	if (!fgets(buffer, 1023, file)) {
		fclose(file);
		return;
	}

	if (strstr(buffer, "hpet")) {
		fclose(file);
		return;
	}

	fclose(file);

	add_suggestion( _("Suggestion: enable the HPET (Multimedia Timer) in your BIOS or add \n"
		          "the kernel patch to force-enable HPET. HPET support allows Linux to \n"
			  "have much longer sleep intervals."), 7, 0, NULL, NULL);
}
