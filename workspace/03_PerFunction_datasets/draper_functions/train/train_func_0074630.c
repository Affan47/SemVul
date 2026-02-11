dupwin ( WINDOW *orig ) {
	WINDOW *copy;
	if ( orig == NULL )
		return NULL;
	if ( ( copy = malloc( sizeof( WINDOW ) ) ) == NULL )
		return NULL;
	copy->scr = orig->scr;
	copy->attrs = orig->attrs;
	copy->ori_y = orig->ori_y;
	copy->ori_x = orig->ori_x;
	copy->curs_y = orig->curs_y;
	copy->curs_x = orig->curs_x;
	copy->height = orig->height;
	copy->width = orig->width;
	return copy;
}
