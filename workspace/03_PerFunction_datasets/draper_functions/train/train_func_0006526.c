find_parameters ( const char *name ) {
	struct parameters *params;

	list_for_each_entry ( params, &parameters, list ) {
		if ( ( params->name == name ) ||
		     ( strcmp ( params->name, name ) == 0 ) ) {
			return params;
		}
	}
	return NULL;
}
