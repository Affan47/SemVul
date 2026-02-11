ipmi_pef_print_field(const char * fmt[2], const char * label, unsigned long val)
{


	if (verbose)
		printf(fmt[0], KYWD_LENGTH, label, val);
	else if (first_field)
		printf(&fmt[1][2], val);
	else
		printf(fmt[1], val);

	first_field = 0;
}
