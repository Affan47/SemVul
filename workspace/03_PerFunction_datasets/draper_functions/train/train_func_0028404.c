gui_logo (PRN *prn)
{
    PRN *myprn = NULL;

    if (prn == NULL) {
	myprn = gretl_print_new(GRETL_PRINT_STDOUT, NULL);
	prn = myprn;
    }

    pprintf(prn, _("gretl: gui client for gretl version %s,\n"), GRETL_VERSION);
    pputs(prn, _("Copyright Allin Cottrell and Riccardo \"Jack\" Lucchetti"));
    pputc(prn, '\n');
    pputs(prn, _("This is free software with ABSOLUTELY NO WARRANTY"));
    pputc(prn, '\n');

    if (myprn != NULL) {
	gretl_print_destroy(myprn);
    }
}
