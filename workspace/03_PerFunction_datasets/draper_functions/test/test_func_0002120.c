gamgi_expat_import_gml (char *filename,
gamgi_window *window)
{
XML_Parser parser;
gamgi_gml *gml;
int valid;


parser = XML_ParserCreate (NULL);
gml = static_create_gml (parser, window);
XML_SetUserData (parser, gml);


XML_SetStartDoctypeDeclHandler (parser, static_doctype_gml);
XML_SetCharacterDataHandler (parser, static_cdata_gml);
XML_SetStartElementHandler (parser, gamgi_expat_import_object_start);
XML_SetEndElementHandler (parser, gamgi_expat_import_object_end);
XML_SetExternalEntityRefHandler (parser, static_entity_gml);


valid = static_import_gml (filename, GAMGI_CAST_ML gml);
XML_ParserFree(parser);

if (valid == TRUE)
  {


  gamgi_gtk_history_update (window->layer,
  window->layer->undo, GAMGI_ENGINE_UNDO);

  static_object (gml);
  static_config (gml);
  }

static_remove (gml, valid);

return valid;
}
