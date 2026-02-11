move_down(Field *field, Block *block){
	Block tempblock = *block;
	tempblock.posy++;

	if(is_obstructed(field, &tempblock)){
		return -1;
	}

	*block = tempblock;
	return 0;
}
