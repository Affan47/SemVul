xmlrc_parse_file_exts(xmlDocPtr doc, xmlNodePtr cur)
{
  GList      *file_exts;
  file_ext_t *file_ext;

  file_exts = NULL;
  cur = cur->xmlChildrenNode;
  while (cur)
  {
    if (xmlStrcmp(cur->name, (const xmlChar *) "file_ext"))
      ERR("cur->name:%s unknown", cur->name);
    file_ext = xmlrc_parse_file_ext(doc, cur);
    if (file_ext != NULL)
      file_exts = g_list_append(file_exts, file_ext);

    cur = cur->next;
  }
  return file_exts;
}
