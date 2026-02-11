sb_xml_write_just(String_buf sb, Just just, I3list map)
{
  Just g;


  String_buf sb_standard = get_string_buf();
  sb_write_just(sb_standard, just, map);
  sb_append(sb, "    <justification jstring=\"");
  sb_cat(sb, sb_standard);
  sb_append(sb, "\">\n");


  for (g = just; g; g = g->next) {

    Ilist parents = get_parents(g, FALSE);

    if (g == just)
      sb_append(sb, "      <j1 rule=\"");
    else
      sb_append(sb, "      <j2 rule=\"");
    sb_append(sb, jstring(g));
    sb_append(sb, "\"");

    if (parents) {
      sb_append(sb, " parents=\"");
      sb_write_ids(sb, parents, map);
      zap_ilist(parents);
      sb_append(sb, "\"");
    }

    sb_append(sb, "/>\n");
  }
  sb_append(sb, "    </justification>\n");
}
