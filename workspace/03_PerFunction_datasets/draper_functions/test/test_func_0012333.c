stuff_int(int *i)
{
	*i = atoi2();

	if (my_errno)
		skip_token();
	else
		Mp += strspn(Mp, "+-0123456789");

	if (*Mp ==',')
		Mp++;

	diag_printf("Stuffed int: %i\n", *i);
}
