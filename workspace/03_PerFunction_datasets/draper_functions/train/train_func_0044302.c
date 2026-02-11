perl_line_fill_hash(HV *hv, LINE_REC *line)
{
	hv_store(hv, "info", 4, plain_bless(&line->info, "Irssi::TextUI::LineInfo"), 0);
}
