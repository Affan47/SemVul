script_new_line (void)
{

	if (fputc ('\n', sfp) == EOF)
		script_close ();

	script_width = 0;

}
