save_filtered_in_dos_mode(GFileOutputStream* stream, gchar *data_,
						  gsize size)
{
	gboolean result;
	gsize i, j;
	unsigned char *data;
	unsigned char *tr_map;
	int k;


	tr_map = malloc( 256 );
	memset( tr_map, 0, 256 );

	for ( k = 0; k < sizeof(tr_dos)/2; k++)
	  tr_map[tr_dos[k].c] = tr_dos[k].b;

	data = (unsigned char*)data_;
	i = 0;
	j = 0;
	while ( i < size )
	{
		if (data[i]>=128)
		{

			if ( tr_map[data[i]] != 0 )
			{
				gsize bytes_written;
				result = g_output_stream_write_all (G_OUTPUT_STREAM (stream),
														&tr_map[data[i]], 1,
														&bytes_written,
														NULL, NULL);

				j += bytes_written;
			}
			else
			{

				gsize bytes_written;
				result = g_output_stream_write_all (G_OUTPUT_STREAM (stream),
														&data[i], 1,
														&bytes_written,
														NULL, NULL);
				j += bytes_written;
			}
			i++;
		}
		else
		{
			gsize bytes_written;
			result = g_output_stream_write_all (G_OUTPUT_STREAM (stream),
														&data[i], 1,
														&bytes_written,
														NULL, NULL);
			j += bytes_written;
			i++;
		}
		if (!result)
			break;
	}

	if (tr_map)
		free (tr_map);
	return result;
}
