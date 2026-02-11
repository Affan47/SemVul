read_image(void)
{
    FILE *fp;
    unsigned int i, j;
    int magic;
    unsigned int maxval;


    fp = fopen(filename, "r");
    if (!fp)
	die("Cannot open file %s: %s\n", filename, strerror(errno));


    magic = fgetc(fp);
    if (magic != 'P')
	die("%s is not a PNM file\n", filename);
    magic = fgetc(fp);
    switch (magic) {
	case '1':
	case '2':
	case '3':

	    break;

	case '4':
	case '5':
	case '6':

	    die("%s: Binary PNM is not supported\n"
		"Use pnmnoraw(1) to convert it to ASCII PNM\n", filename);

	default:
	    die("%s is not a PNM file\n", filename);
    }
    logo_width = get_number(fp);
    logo_height = get_number(fp);


    logo_data = (struct color **)malloc(logo_height*sizeof(struct color *));
    if (!logo_data)
	die("%s\n", strerror(errno));
    for (i = 0; i < logo_height; i++) {
	logo_data[i] = malloc(logo_width*sizeof(struct color));
	if (!logo_data[i])
	    die("%s\n", strerror(errno));
    }


    switch (magic) {
	case '1':

	    is_plain_pbm = 1;
	    for (i = 0; i < logo_height; i++)
		for (j = 0; j < logo_width; j++)
		    logo_data[i][j].red = logo_data[i][j].green =
			logo_data[i][j].blue = 255*(1-get_number(fp));
	    break;

	case '2':

	    maxval = get_number(fp);
	    for (i = 0; i < logo_height; i++)
		for (j = 0; j < logo_width; j++)
		    logo_data[i][j].red = logo_data[i][j].green =
			logo_data[i][j].blue = get_number255(fp, maxval);
	    break;

	case '3':

	    maxval = get_number(fp);
	    for (i = 0; i < logo_height; i++)
		for (j = 0; j < logo_width; j++) {
		    logo_data[i][j].red = get_number255(fp, maxval);
		    logo_data[i][j].green = get_number255(fp, maxval);
		    logo_data[i][j].blue = get_number255(fp, maxval);
		}
	    break;
    }


    fclose(fp);
}
