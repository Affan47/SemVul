gGraphImageInfosFromHgtFile (const char *path, int lat, int lon,
			     const void **infos_handle)
{

    FILE *in = NULL;
    gGraphImageInfosPtr infos = NULL;
    long file_length;
    int width;
    int height;
    double pixel_size;
    double half_pixel;

    *infos_handle = NULL;


    in = fopen (path, "rb");
    if (in == NULL)
	return GGRAPH_FILE_OPEN_ERROR;


    if (fseek (in, 0, SEEK_END) != 0)
	return GGRAPH_HGT_CODEC_ERROR;
    file_length = ftell (in);
    if (file_length == (1201 * 1201 * sizeof (short)))
      {
	  width = 1201;
	  height = 1201;
	  pixel_size = 1.0 / 1200.0;
      }
    else if (file_length == (3601 * 3601 * sizeof (short)))
      {
	  width = 3601;
	  height = 3601;
	  pixel_size = 1.0 / 3600.0;
      }
    else
      {
	  fclose (in);
	  return GGRAPH_HGT_CODEC_ERROR;
      }
    fclose (in);

    infos =
	gg_image_infos_create (GG_PIXEL_GRID, width, height, 16, 1,
			       GGRAPH_SAMPLE_INT, "WGS 84",
			       "+proj=longlat +ellps=WGS84 +datum=WGS84 +no_defs");
    if (!infos)
	return GGRAPH_INSUFFICIENT_MEMORY;


    half_pixel = pixel_size / 2.0;
    infos->is_georeferenced = 1;
    infos->srid = 4326;
    infos->upper_left_x = (double) lon - half_pixel;
    infos->upper_left_y = (double) lat + 1.0 + half_pixel;
    infos->pixel_x_size = pixel_size;
    infos->pixel_y_size = pixel_size;
    infos->no_data_value = SHRT_MIN;

    *infos_handle = infos;
    return GGRAPH_OK;
}
