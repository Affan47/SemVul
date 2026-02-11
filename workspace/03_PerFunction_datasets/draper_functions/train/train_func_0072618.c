releaseframechunkdata( struct FLI *fli ) {
struct FLI_FRAMECHUNK *fc;
	fc = fli->frame + fli->current;
	if( fc->cd ) {
		free( fc->cd );
		fc->cd = NULL;
	}
}
