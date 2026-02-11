text_debug(Text *txt) {
	for (Piece *p = &txt->begin; p; p = p->next) {
		print_piece(p);
	}
}
