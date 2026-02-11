static_br_start (const char *element,
const char **attributes, gamgi_html *html)
{
int fileline;


fileline = XML_GetCurrentLineNumber (html->ml.parser);


if (gamgi_expat_import_parent_html (GAMGI_EXPAT_BR, html) == FALSE)
  return gamgi_io_error_child (html->ml.filename,
  fileline, html->ml.window);


html->ml.parent = gamgi_engine_slist_add_start (html->ml.parent);
html->ml.parent->data = (void *) GAMGI_EXPAT_BR;


if (attributes[0] != NULL)
  return gamgi_io_error_attribute (attributes[0],
  html->ml.filename, fileline, html->ml.window);


gtk_text_buffer_insert_with_tags_by_name (html->buffer,
&html->iter, "\n", 1, html->size, html->color, NULL);

return html->ml.valid;
}
