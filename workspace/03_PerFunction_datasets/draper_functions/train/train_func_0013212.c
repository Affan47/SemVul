diagnostic_append_note (diagnostic_context *context,
                        location_t location,
                        const char * gmsgid, ...)
{
  diagnostic_info diagnostic;
  va_list ap;
  const char *saved_prefix;

  va_start (ap, gmsgid);
  diagnostic_set_info (&diagnostic, gmsgid, &ap, location, DK_NOTE);
  if (context->inhibit_notes_p)
    {
      va_end (ap);
      return;
    }
  saved_prefix = pp_get_prefix (context->printer);
  pp_set_prefix (context->printer,
                 diagnostic_build_prefix (context, &diagnostic));
  pp_newline (context->printer);
  pp_format (context->printer, &diagnostic.message);
  pp_output_formatted_text (context->printer);
  pp_destroy_prefix (context->printer);
  pp_set_prefix (context->printer, saved_prefix);
  diagnostic_show_locus (context, &diagnostic);
  va_end(ap);
}
