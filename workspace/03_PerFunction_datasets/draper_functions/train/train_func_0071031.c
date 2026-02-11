waveformNew(waveform_ *r, control_ *control, char type,
		double *args[7], double **dcPtr)
{
	ReturnNULLIf(r != NULL);
	ReturnNULLIf(control == NULL);
	ReturnNULLIf((type != 'p') && (type != 'g') && (type != 's') &&
			(type != 'e') && (type != 'l') && (type != 'c') && (type != 'f'));
	ReturnNULLIf(args == NULL);

	r = calloc(1, sizeof(waveform_));
	ReturnNULLIf(r == NULL, "Malloc Failed");

	Debug("Creating Waveform %p", r);

	r->type = type;
	r->control = control;
	ReturnNULLIf(waveformParseArgs(r, args, dcPtr));

	return r;
}
