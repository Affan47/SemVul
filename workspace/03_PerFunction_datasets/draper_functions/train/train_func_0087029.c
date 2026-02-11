graph_pad_horizontally(struct git_graph *graph, struct strbuf *sb,
				   int chars_written)
{


	int extra;
	if (chars_written >= graph->width)
		return;

	extra = graph->width - chars_written;
	strbuf_addf(sb, "%*s", (int) extra, "");
}
