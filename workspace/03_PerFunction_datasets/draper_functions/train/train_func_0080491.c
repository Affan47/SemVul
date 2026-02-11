set_cube_map(
	CL_PixelBuffer &cube_map_positive_x,
	CL_PixelBuffer &cube_map_negative_x,
	CL_PixelBuffer &cube_map_positive_y,
	CL_PixelBuffer &cube_map_negative_y,
	CL_PixelBuffer &cube_map_positive_z,
	CL_PixelBuffer &cube_map_negative_z,
	int level,
	int border,
	int format)
{
	if (impl->target != CL_TEXTURE_CUBE_MAP)
		throw CL_Error("CL_Texture::set_cube_map does not support this texture format");

	CL_PixelBuffer cube_maps[6];
	cube_maps[0] = cube_map_positive_x;
	cube_maps[1] = cube_map_negative_x;
	cube_maps[2] = cube_map_positive_y;
	cube_maps[3] = cube_map_negative_y;
	cube_maps[4] = cube_map_positive_z;
	cube_maps[5] = cube_map_negative_z;
	CLenum native_format[6];
	CLenum native_type[6];
	int index_maps;


	for (index_maps = 0; index_maps < 6; index_maps++)
	{
		bool is_native_format = CL_OpenGL::to_opengl_pixelformat(
			cube_maps[index_maps].get_format(),
			native_format[index_maps],
			native_type[index_maps]);
		if (!is_native_format)
		{
			cube_maps[index_maps] = cube_maps[index_maps].to_format(CL_PixelFormat::rgba8888);
			is_native_format = CL_OpenGL::to_opengl_pixelformat(
				cube_maps[index_maps].get_format(),
				native_format[index_maps],
				native_type[index_maps]);
		}
	}


	int targets[6] =
	{
		CL_TEXTURE_CUBE_MAP_POSITIVE_X,
		CL_TEXTURE_CUBE_MAP_NEGATIVE_X,
		CL_TEXTURE_CUBE_MAP_POSITIVE_Y,
		CL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
		CL_TEXTURE_CUBE_MAP_POSITIVE_Z,
		CL_TEXTURE_CUBE_MAP_NEGATIVE_Z
	};

	for (index_maps = 0; index_maps < 6; index_maps++)
	{
		cube_maps[index_maps].lock();
		set_image2d_gl(
			targets[index_maps],
			level,
			(format == 0) ? native_format[index_maps] : format,
			cube_maps[index_maps].get_width(),
			cube_maps[index_maps].get_height(),
			border,
			native_format[index_maps],
			native_type[index_maps],
			cube_maps[index_maps].get_data());
		cube_maps[index_maps].unlock();
	}
}
