SVGEndDocument(void *context)
{
  SVGInfo
    *svg_info;


  (void) LogMagickEvent(CoderEvent,GetMagickModule(),"  SAX.endDocument()");
  svg_info=(SVGInfo *) context;
  MagickFreeMemory(svg_info->offset);
  MagickFreeMemory(svg_info->stop_color);
  MagickFreeMemory(svg_info->scale);
  MagickFreeMemory(svg_info->text);
  MagickFreeMemory(svg_info->vertices);
  MagickFreeMemory(svg_info->url);
  if (svg_info->document != (xmlDocPtr) NULL)
    {
      xmlFreeDoc(svg_info->document);
      svg_info->document=(xmlDocPtr) NULL;
    }
}
