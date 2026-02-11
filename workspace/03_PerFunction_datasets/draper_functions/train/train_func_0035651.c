accur_error_total ()
{
	gint i;
	gulong n = 0;

	for (i = 0; i < terror_n; i++)
		n += (terror[i].wrong < 12345 ? terror[i].wrong : 0);

	return n;
}
