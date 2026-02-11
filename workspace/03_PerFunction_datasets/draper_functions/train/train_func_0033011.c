write_menubar_tp(FILE *fh, menubar_t **foo)
{
	if (*foo) {


  _cfsml_write_menubar_t(fh, (*foo));
  fprintf(fh, "\n");


	} else {
		fputs("\\null\\", fh);
	}
}
