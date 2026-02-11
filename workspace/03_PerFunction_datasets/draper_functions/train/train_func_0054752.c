dsgw_body( int argc, char **argv)
{
    char line[BIG_LINE];

    if ( argc > 0 ) {
	PR_snprintf(line, sizeof(line), "<BODY %s %s>\n", dsgw_html_body_colors,
		( argc > 0 ) ? argv[0] : "" );
    } else {
	PR_snprintf(line, sizeof(line), "<BODY %s>\n", dsgw_html_body_colors );
    }

    dsgw_emits(line);
}
