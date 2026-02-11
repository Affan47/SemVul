get_ghost_piece(Field *field, Block *block){
	Block tempblock = *block;

	while(!is_obstructed(field, &tempblock)) {
		tempblock.posy++;
	}
	tempblock.posy--;

	return tempblock;
}
