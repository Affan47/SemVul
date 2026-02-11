dcd_delta_fli( struct FLI *fli, char *data ) {
short int line;
short int nrlines;
char *index;
uchar packets;
int index_x;
char type;

	line = *(short int *)data;
	data = (void *)((short int *)data + 1);
	index = graph_mem + line * fli->scr_width;
	nrlines = *(short int *)data;
	data = (void *)((short int *)data + 1);
	while( nrlines-- > 0 ) {
		index_x = 0;
		packets = *(uchar *)data;
		data = (void *)((uchar *)data + 1);
		while( packets > 0 ) {
			index_x += *(uchar *)data;
			data = (void *)((uchar *)data + 1);
			type = *(char *)data;
			data = (void *)((char *)data + 1);
			if( type >= 0 ) {
				memcpy( index + index_x, data, type );
				index_x += type;
				data = (void *)((uchar *)data + type);
				packets--;
				continue;
			}
			memset( index + index_x, *(uchar *)data, -type );
			index_x -= type;
			data = (void *)((uchar *)data + 1);
			packets--;
		}
		index += fli->scr_width;
	}
}
