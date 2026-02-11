mix_stereo( blip_sample_t* out_, blargg_long count )
{
	blip_sample_t* BLIP_RESTRICT out = out_;
	int const bass = BLIP_READER_BASS( bufs [0] );
	BLIP_READER_BEGIN( c, bufs [0] );
	BLIP_READER_BEGIN( l, bufs [1] );
	BLIP_READER_BEGIN( r, bufs [2] );

	while ( count-- )
	{
		int cs = BLIP_READER_READ( c );
		BLIP_READER_NEXT( c, bass );
		int left = cs + BLIP_READER_READ( l );
		int right = cs + BLIP_READER_READ( r );
		BLIP_READER_NEXT( l, bass );
		BLIP_READER_NEXT( r, bass );

		if ( (int16_t) left != left )
			left = 0x7FFF - (left >> 24);

		out [0] = left;
		out [1] = right;

		out += 2;

		if ( (int16_t) right != right )
			out [-1] = 0x7FFF - (right >> 24);
	}

	BLIP_READER_END( r, bufs [2] );
	BLIP_READER_END( l, bufs [1] );
	BLIP_READER_END( c, bufs [0] );
}
