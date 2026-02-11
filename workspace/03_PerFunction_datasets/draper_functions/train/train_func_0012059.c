parseCommandlineColor(char* the_color)
{
	BColor color;

	char temp_red[3] = "/0";
	char temp_green[3]= "/0";
	char temp_blue[3]= "/0";

	for (int i=0; i<6; i++)
	{
		temp_red[0] = the_color[i++];
		temp_red[1] = the_color[i++];
		temp_green[0] = the_color[i++];
		temp_green[1] = the_color[i++];
		temp_blue[0] = the_color[i++];
		temp_blue[1] = the_color[i];
	}

	color.red = strtol(temp_red,0,16);
	color.green = strtol(temp_green,0,16);
	color.blue = strtol(temp_blue,0,16);

	return color;
}
