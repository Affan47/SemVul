stuff_float(float *f)
{
	*f = atof2();

	if (my_errno)
		skip_token();
	else
		Mp += strspn(Mp, "+-0123456789.");

	if (*Mp ==',')
		Mp++;

	diag_printf("Stuffed float: %f\n", *f);
}
