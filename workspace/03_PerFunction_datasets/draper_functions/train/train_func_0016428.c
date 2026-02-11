ce_start(void* data, const XML_Char* xml_el, const XML_Char** xml_attr)
{
  const char* el = xml_convert_to_char_string(xml_el);
  const char** ap;
  const char** attr;

  attr = xml_convert_attrs_to_char_string(xml_attr);
  strcpy(element, el);
  if (0 == strcmp(el, "Route")) {
    inRoute = 1;
    for (ap = attr; *ap; ap+=2) {
      if (0 == strcmp(ap[0], "id")) {

        currentRoute = (ce_route*) xcalloc(sizeof(ce_route), 1);
        currentRoute->id=xstrdup(ap[1]);
        currentRoute->r = route_head_alloc();
        QUEUE_INIT(&currentRoute->ce_mark_head);
        ce_add_route(currentRoute);
      }
    }
  } else if (0 == strcmp(el, "Mark")) {
    inMark = 1;
    currentMark = ce_alloc_mark(NULL, NULL);
    ce_add_mark(currentMark);
    for (ap = attr; *ap; ap+=2) {
      if (0 == strcmp(ap[0], "id")) {

        currentMark->id = xstrdup(ap[1]);
      } else if (0 == strcmp(ap[0], "created")) {
        currentMark->created = xstrdup(ap[1]);
      }
    }
  }
  xml_free_converted_string(el);
  xml_free_converted_attrs(attr);
}
