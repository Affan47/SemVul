read_menubar_tp(FILE *fh, menubar_t **foo, char *lastval, int *line, int *hiteof)
{

	if (lastval[0] == '\\') {
		*foo = NULL;
	} else {

		*foo = (menubar_t *) sci_malloc(sizeof(menubar_t));

  {
    int _cfsml_eof = 0, _cfsml_error;
    int dummy;
    char *_cfsml_inp = lastval;
    _cfsml_error = _cfsml_read_menubar_t(fh, (*foo), _cfsml_inp, &(*line), &_cfsml_eof);
    *hiteof = _cfsml_error;
     if (_cfsml_last_value_retreived) {
       free(_cfsml_last_value_retreived);
       _cfsml_last_value_retreived = NULL;
     }
     if (_cfsml_last_identifier_retreived) {
       free(_cfsml_last_identifier_retreived);
       _cfsml_last_identifier_retreived = NULL;
     }
  }


	}
	return *hiteof;
}
