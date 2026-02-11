write_to_stream(std::ostream& os, int scale)
{
	os << "P6 " << my_width * scale << " " << my_height * scale << " 255\n";
	for(int y = 0; y < my_height * scale; y++)
		for(int x = 0; x < my_width * scale; x++)
		{
			int index = int(x / scale) + int(y / scale) * my_width;
			os << red[index] << green[index] << blue[index];
		}
}
