SaveSettings(void)
{


	int             tmp, ii;
	setfile = OpenDefaultFile("w");
	if (setfile == NULL)
		return EFILE;
	ErrorExitWarn(ReadRecSrc(), 'e');
	for (ii = 0; ii < SOUND_MIXER_NRDEVICES; ii++) {
		if ((1 << ii) & (devmask | recmask)) {
			ErrorExitWarn(ReadLevel(ii, &tmp), 'e');
			fprintf(setfile, "%s:%i:%i:%c\n", dev_name[ii], (tmp & 0xFF), ((tmp >> 8) & 0xFF), ((1 << ii) & recsrc ? 'R' : 'P'));
		}
	}
	if (fclose(setfile))
		return EFILE;
	return 0;
}
