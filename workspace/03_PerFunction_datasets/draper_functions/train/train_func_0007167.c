gamgi_io_x3d_render_wired (FILE *fp, gamgi_text *text, gamgi_bool *error)
{
	int c = 0;
	int i, j;
	int * driver = 0;
	float * points = 0;
	char str[256];
	float spacing;

gamgi_mesa_text_data_wired (text->font, (const float **) &points, (const int **) &driver);

	gamgi_io_file_fprintf(fp, "<IndexedLineSet coordIndex='", error);


	for(i=0; i<text->length; i++)
	{
		j = driver[text->string[i]-GAMGI_IO_ASCII_START];

		while(points[j] != GAMGI_IO_CHAR)
		{
			if(points[j] == GAMGI_IO_STROKE)
			{
				gamgi_io_file_fprintf(fp, "-1, ", error);
				j++;
			}
			else
			{
				sprintf(str, "%d, ", c);
				gamgi_io_file_fprintf(fp, str, error);
				c++;
				j+=2;
			}
		}

		if(i<text->length-1)
			gamgi_io_file_fprintf(fp, "-1, ", error);
	}

	gamgi_io_file_fprintf(fp, "-1'>\n<Coordinate point='", error);
	spacing = 0.0f;

	for(i=0; i<text->length; i++)
	{
		j = driver[text->string[i]-GAMGI_IO_ASCII_START];

		while(points[j] != GAMGI_IO_CHAR)
		{
			if(points[j] != GAMGI_IO_STROKE)
			{
				sprintf(str, "%f %f 0.0", points[j]/GAMGI_MESA_STROKED_SCALE+spacing, points[j+1]/GAMGI_MESA_STROKED_SCALE);
				gamgi_io_file_fprintf(fp, str, error);
				j+=2;

				if(i<text->length-1 || points[j] != GAMGI_IO_CHAR)
					gamgi_io_file_fprintf(fp, ", ", error);
			}
			else
			{
				j++;
			}
		}

		spacing += points[text->string[i]-GAMGI_IO_ASCII_START+2]/GAMGI_MESA_STROKED_SCALE;
	}

	gamgi_io_file_fprintf(fp, "'/>\n</IndexedLineSet>\n", error);
}
