script_data_segment_relro_end(void* closurev)
{
  Parser_closure* closure = static_cast<Parser_closure*>(closurev);
  if (!closure->script_options()->saw_sections_clause())
    gold_error(_("%s:%d:%d: DATA_SEGMENT_ALIGN not in SECTIONS clause"),
	       closure->filename(), closure->lineno(), closure->charpos());
  else
    closure->script_options()->script_sections()->data_segment_relro_end();
}
