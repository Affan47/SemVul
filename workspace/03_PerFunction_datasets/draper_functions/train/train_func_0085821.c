gx_rack_tuner_pitch_to_note(GxRackTuner *tuner, double fnote, int *oc, int *note, double *scale)
{
	double fnoter = round(fnote);
	*note = int(fnoter);
	if (scale) {
		*scale = fnote - *note;
	}
	*oc = int(round(fnoter/12));
	int octsz = sizeof(octave) / sizeof(octave[0]);
	if (*oc < 0 || *oc >= octsz) {
		*oc = octsz - 1;
	}
	*note = *note % 12;
	if (*note < 0) {
		*note += 12;
	}
}
