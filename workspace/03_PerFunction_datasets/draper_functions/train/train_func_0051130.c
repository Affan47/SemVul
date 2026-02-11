assign_graphics(graph_chars, glth, maxlen, offset)
register uchar *graph_chars;
int glth, maxlen, offset;
{
    register int i;

    for (i = 0; i < maxlen; i++)
	showsyms[i+offset] = (((i < glth) && graph_chars[i]) ?
		       graph_chars[i] : defsyms[i+offset].sym);
}
