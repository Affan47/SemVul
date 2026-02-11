gGraphImageInfosFromAscFile (const char *path, const void **infos_handle)
{

    gGraphImageInfosPtr infos = NULL;
    int width;
    int height;
    double ulx;
    double uly;
    double pixel_x_size;
    double pixel_y_size;
    double no_data;

    *infos_handle = NULL;

    if (!parse_asc_hdr
	(path, NULL, &width, &height, &ulx, &uly, &pixel_x_size, &pixel_y_size,
	 &no_data))
	return GGRAPH_ASCII_CODEC_ERROR;

    infos =
	gg_image_infos_create (GG_PIXEL_GRID, width, height, 32, 1,
			       GGRAPH_SAMPLE_FLOAT, NULL, NULL);
    if (!infos)
	return GGRAPH_INSUFFICIENT_MEMORY;


    infos->is_georeferenced = 1;
    infos->upper_left_x = ulx;
    infos->upper_left_y = uly;
    infos->pixel_x_size = pixel_x_size;
    infos->pixel_y_size = pixel_y_size;
    infos->no_data_value = no_data;

    *infos_handle = infos;
    return GGRAPH_OK;
}
