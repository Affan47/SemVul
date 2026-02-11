parse_bsp(int offset, ubyte *bsp_data)
{
	int id = w(bsp_data+offset);
	int size = w(bsp_data+offset+4);

	while (id != 0) {
		switch (id)
		{
			case OP_EOF:
				return;

			case OP_DEFPOINTS:
				parse_defpoint(offset, bsp_data);
				break;

			case OP_SORTNORM:
				parse_sortnorm(offset, bsp_data);
				break;

			case OP_FLATPOLY:
				break;

			case OP_TMAPPOLY:
				parse_tmap(offset, bsp_data);
				break;

			case OP_BOUNDBOX:
				break;

			default:
				return;
		}

		offset += size;
		id = w(bsp_data+offset);
		size = w(bsp_data+offset+4);

		if (size < 1)
			id = OP_EOF;
	}
}
