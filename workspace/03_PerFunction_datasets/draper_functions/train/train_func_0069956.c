display (cob_field *f, FILE *fp)
{
	unsigned char	*p;
	int		n;
	cob_field	temp;
	cob_field_attr	attr;

	if (COB_FIELD_TYPE (f) == COB_TYPE_NUMERIC_DOUBLE) {
		double f1doub;

		memcpy ((char *)&f1doub, f->data, sizeof (double));
		fprintf (fp, "%-.18lf", f1doub);
	} else if (COB_FIELD_TYPE (f) == COB_TYPE_NUMERIC_FLOAT) {
		float f1float;

		memcpy ((char *)&f1float, f->data, sizeof (float));
		fprintf (fp, "%-.18lf", (double)f1float);
	} else if (COB_FIELD_IS_POINTER (f)) {
		fprintf (fp, "0x");
#ifdef WORDS_BIGENDIAN
		p = f->data;
		for (n = 0; n < sizeof(void *); ++n, ++p) {
#else
		p = f->data + sizeof(void *) - 1;
		for (n = sizeof(void *) - 1; n >= 0; --n, --p) {
#endif
			fprintf (fp, "%x%x", *p >> 4, *p & 0xF);
		}
	} else if (COB_FIELD_REAL_BINARY(f) ||
		   (COB_FIELD_TYPE(f) == COB_TYPE_NUMERIC_BINARY
		    && !cob_current_module->flag_pretty_display)) {
		attr = *f->attr;
		temp = *f;
		attr.digits = bin_digits[f->size];
		temp.attr = &attr;
		display_numeric (&temp, fp);
	} else if (COB_FIELD_IS_NUMERIC (f)) {
		if (cob_current_module->flag_pretty_display) {
			pretty_display_numeric (f, fp);
		} else {
			display_numeric (f, fp);
		}
	} else {
		display_alnum (f, fp);
	}
}
