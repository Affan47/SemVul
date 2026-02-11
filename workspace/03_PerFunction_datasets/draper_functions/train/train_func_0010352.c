write_logo_clut224(void)
{
    unsigned int i, j, k;


    for (i = 0; i < logo_height; i++)
	for (j = 0; j < logo_width; j++) {
	    for (k = 0; k < logo_clutsize; k++)
		if (is_equal(logo_data[i][j], logo_clut[k]))
		    break;
	    if (k == logo_clutsize) {
		if (logo_clutsize == MAX_LINUX_LOGO_COLORS)
		    die("Image has more than %d colors\n"
			"Use ppmquant(1) to reduce the number of colors\n",
			MAX_LINUX_LOGO_COLORS);
		logo_clut[logo_clutsize++] = logo_data[i][j];
	    }
	}


    write_header();


    for (i = 0; i < logo_height; i++)
	for (j = 0; j < logo_width; j++) {
	    for (k = 0; k < logo_clutsize; k++)
		if (is_equal(logo_data[i][j], logo_clut[k]))
		    break;
	    write_hex(k+32);
	}
    fputs("\n};\n\n", out);


    fprintf(out, "static unsigned char %s_clut[] __initdata = {\n",
	    logoname);
    write_hex_cnt = 0;
    for (i = 0; i < logo_clutsize; i++) {
	write_hex(logo_clut[i].red);
	write_hex(logo_clut[i].green);
	write_hex(logo_clut[i].blue);
    }


    write_footer();
}
