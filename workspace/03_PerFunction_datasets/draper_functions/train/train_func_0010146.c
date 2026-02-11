cleanPieces() {
    int32_t i = 0;
    if(pieces != NULL) {
        for(i = 0; i < pieces_length; i++) {
            if(pieces[i] != NULL) {
                delete[] pieces[i];
            }
        }
        uprv_free(pieces);
        pieces = NULL;
        pieces_length = 0;
    }
    if(pieces_lengths != NULL) {
        uprv_free(pieces_lengths);
        pieces_lengths = NULL;
    }
    if(current != NULL) {
        uprv_free(current);
        current = NULL;
        current_length = 0;
    }
}
