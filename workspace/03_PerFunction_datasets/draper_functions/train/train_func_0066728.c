bbusters_draw_block(struct mame_bitmap *dest,int x,int y,int size,int flipx,int flipy,unsigned int sprite,int color,int bank,int block)
{
	const pen_t *pal = &Machine->gfx[bank]->colortable[Machine->gfx[bank]->color_granularity * (color % Machine->gfx[bank]->total_colors)];
	unsigned int xinc=(scale_line_count * 0x10000 ) / size;
	data8_t pixel;
	int x_index;
	int dy=y;
	int sx,ex=scale_line_count;

	while (scale_line_count) {

		if (dy>=16 && dy<240) {
			UINT16 *destline = (UINT16 *)dest->line[dy];
			data8_t srcline=*scale_table_ptr;
			const data8_t *srcptr=0;

			if (!flipy)
				srcline=size-srcline-1;

			if (flipx)
				x_index=(ex-1)*0x10000;
			else
				x_index=0;

			for (sx=0; sx<size; sx++) {
				if ((sx%16)==0)
					srcptr=get_source_ptr(sprite,sx,srcline,bank,block);

				pixel=*srcptr++;
				if (x+(x_index>>16)>=0 && x+(x_index>>16)<256 && pixel!=15)
					destline[x+(x_index>>16)]=pal[pixel];

				if (flipx)
					x_index-=xinc;
				else
					x_index+=xinc;
			}
		}

		dy++;
		scale_table_ptr--;
		scale_line_count--;
	}
}
