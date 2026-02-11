dicod_help(dico_stream_t str, int argc, char **argv)
{
    const char *text = help_text;
    dico_stream_t ostr;

    stream_writez(str, "113 help text follows\n");
    ostr = dicod_ostream_create(str, NULL);

    if (text) {
	if (text[0] == '+') {
	    dicod_show_std_help(ostr);
	    text++;
	}
	stream_write_multiline(ostr, text);
    } else
	dicod_show_std_help(ostr);

    stream_writez(ostr, "\n");
    dico_stream_close(ostr);
    dico_stream_destroy(&ostr);

    stream_writez(str, ".\n");
    stream_writez(str, "250 ok\n");
}
