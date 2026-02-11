pp_base_clear_output_area (pretty_printer *pp)
{
  obstack_free (&pp->buffer->obstack, obstack_base (&pp->buffer->obstack));
  pp->buffer->line_length = 0;
}
