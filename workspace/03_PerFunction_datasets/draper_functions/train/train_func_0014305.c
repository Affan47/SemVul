_g_ir_parser_free (GIrParser *parser)
{
  GList *l;

  if (parser->includes)
    g_strfreev (parser->includes);

  for (l = parser->parsed_modules; l; l = l->next)
    _g_ir_module_free (l->data);

  g_slice_free (GIrParser, parser);
}
