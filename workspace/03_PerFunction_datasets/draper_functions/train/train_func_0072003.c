write_logo_mono(void)
{
    unsigned int i, j;
    unsigned char val, bit;


    for (i = 0; i < logo_height; i++)
	for (j = 0; j < logo_width; j++)
	    if (!is_black(logo_data[i][j]) && !is_white(logo_data[i][j]))
		die("Image must be monochrome\n");


    write_header();


    for (i = 0; i < logo_height; i++) {
	for (j = 0; j < logo_width;) {
	    for (val = 0, bit = 0x80; bit && j < logo_width; j++, bit >>= 1)
		if (logo_data[i][j].red)
		    val |= bit;
	    write_hex(val);
	}
    }


    write_footer();
}
