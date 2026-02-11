parse_bsp(int offset, ubyte *bsp_data){
	int ID, SIZE;

	memcpy(&ID, &bsp_data[offset], sizeof(int));
	memcpy(&SIZE, &bsp_data[offset+sizeof(int)], sizeof(int));

	while(ID!=0){
		switch(ID){
		case OP_EOF:
			return;
			break;
		case OP_DEFPOINTS:	defpoint(offset, bsp_data);
			break;
		case OP_SORTNORM:
			break;
		case OP_FLATPOLY:
			break;
		case OP_TMAPPOLY:
			break;
		case OP_BOUNDBOX:
			break;
		default:
			return;
		}
			offset += SIZE;
		memcpy(&ID, &bsp_data[offset], sizeof(int));
		memcpy(&SIZE, &bsp_data[offset+sizeof(int)], sizeof(int));

		if(SIZE < 1)ID=OP_EOF;
	}
}
