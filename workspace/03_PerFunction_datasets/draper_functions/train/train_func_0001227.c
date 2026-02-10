slk_label ( int labnum ) {
	if ( slks == NULL )
		return NULL;

	return slks->fkeys[labnum].label;
}
