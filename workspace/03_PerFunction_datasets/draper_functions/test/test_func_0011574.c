read_write_pixel( FILE* infile, FILE* outfile ) {
    int red, green, blue;
    if (is_ascii()) fscanf(infile, "%d", &red); else red = getc(infile);
    putc(red, outfile);
    if (is_ascii()) fscanf(infile, "%d", &green); else green = getc(infile);
    putc(green, outfile);
    if (is_ascii()) fscanf(infile, "%d", &blue); else blue = getc(infile);
    putc(blue, outfile);
}
