gtc_crs_hdr(const route_head* rte)
{

  gtc_write_xml(1, "<Course>\n");
  gtc_lap_start(NULL);
  gtc_new_study_lap(rte);
  route_disp(rte, gtc_study_lap);
  if (rte->rte_name) {
    char* name = xstrndup(rte->rte_name, GTC_MAX_NAME_LEN);
    gtc_write_xml(0, "<Name>%s</Name>\n", name);
    xfree(name);
  } else {
    gtc_write_xml(0, "<Name>New Course</Name>\n");
  }

  gtc_write_xml(1, "<Lap>\n");
  gtc_fake_hdr();
  gtc_write_xml(-1, "</Lap>\n");
  xfree(tdata);
  gtc_write_xml(1,"<Track>\n");
}
