do_indent(char_io *io_ch, void *arg, int indent)
{
	int i;
	for(i = 0; i < indent; i++)
			if(!io_ch(arg, " ", 1)) return 0;
	return 1;
}
