GMT_decode (void *vptr, GMT_LONG k, GMT_LONG type)
{
	float fval;

	switch (type) {
		case 'b':
			fval = (float)(((char *)vptr)[k]);
			break;
		case 's':
			fval = (float)(((short int *)vptr)[k]);
			break;
		case 'i':
		case 'm':
			fval = (float)(((int *)vptr)[k]);
			break;
		case 'f':
			fval = ((float *)vptr)[k];
			break;
		case 'd':
			fval = (float)(((double *)vptr)[k]);
			break;
		default:
			fprintf (stderr, "GMT: Bad call to GMT_decode (gmt_customio.c)\n");
			fval = GMT_f_NaN;
			break;
	}

	return (fval);
}
