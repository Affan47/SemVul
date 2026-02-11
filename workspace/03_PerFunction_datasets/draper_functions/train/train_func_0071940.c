fprint_xml_chain(xml_tag* tag, const waypoint* wpt)
{
  while (tag) {
    if (!tag->cdata && !tag->child) {
      fprint_tag_and_attrs("<", " />", tag);
    } else {
      fprint_tag_and_attrs("<", ">", tag);

      if (tag->cdata) {
        char* tmp_ent;
        tmp_ent = xml_entitize(tag->cdata);
        gbfprintf(ofd, "%s", tmp_ent);
        xfree(tmp_ent);
      }
      if (tag->child) {
        fprint_xml_chain(tag->child, wpt);
      }
      if (wpt && wpt->gc_data->exported &&
          strcmp(tag->tagname, "groundspeak:cache") == 0) {
        xml_write_time(ofd, wpt->gc_data->exported, 0,
                       "groundspeak:exported");
      }
      gbfprintf(ofd, "</%s>\n", tag->tagname);
    }
    if (tag->parentcdata) {


      char* otmp_ent, *tmp_ent = NULL;
      otmp_ent = xml_entitize(tag->parentcdata);
      if (otmp_ent[0] == '\n')
        tmp_ent = otmp_ent+1;
      else
        tmp_ent = otmp_ent;
      gbfprintf(ofd, "%s", tmp_ent);
      xfree(otmp_ent);
    }
    tag = tag->sibling;
  }
}
