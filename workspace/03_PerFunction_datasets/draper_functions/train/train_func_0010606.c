img_dissolve( cairo_t         *cr,
			  cairo_surface_t *image_from,
			  cairo_surface_t *image_to,
			  gdouble          progress )
{
	gint    width,
			height,
			size,
			draw,
			count;
	guchar *data;
	gint    values[RAND_VALS];


	static cairo_surface_t *mask = NULL;
	static gint             filled;
	static gint             stride;

	width  = cairo_image_surface_get_width( image_from );
	height = cairo_image_surface_get_height( image_from );

	cairo_set_source_surface( cr, image_from, 0, 0 );
	cairo_paint( cr );

	cairo_set_source_surface( cr, image_to, 0, 0 );


	if( progress < 0.00001 )
	{
		if( mask )
			cairo_surface_destroy( mask );

		mask = cairo_image_surface_create( CAIRO_FORMAT_A1, width, height );
		stride = cairo_image_surface_get_stride( mask );
		filled = 0;

		return;
	}
	else if( progress > 0.9999 )
	{
		cairo_paint( cr );
		return;
	}


	size = width * height;
	draw = size * progress - filled;
	filled += draw;


	for( count = 0; count < RAND_VALS; count++ )
		values[count] = rand() % size;


	cairo_surface_flush( mask );
	data = cairo_image_surface_get_data( mask );

	for( count = 0; count < draw; count++ )
	{
		gint        row,
					col,
					index,
					shift;
		static gint value = 0;

		value += values[count % RAND_VALS] % size;
		value %= size;
		row = value / width;
		col = value - width * row;

		do
		{
			col++;
			if( col == width )
			{
				col = 0;
				row++;
				row %= height;
			}

			index = row * stride + ( col / 8 );
			shift = col % 8;
		}
		while( data[index] & ( 1 << shift ) );

		data[index] |= ( 1 << shift );
	}
	cairo_surface_mark_dirty( mask );


	cairo_mask_surface( cr, mask, 0, 0 );
}
