kml_write_bitmap_style(kml_point_type pt_type, const char* bitmap,
                                   const char* customstyle)
{
  int force_heading = 0;
  const char* style;
  switch (pt_type) {
  case kmlpt_track:
    style = "track";
    break;
  case kmlpt_route:
    style = "route";
    break;
  case kmlpt_waypoint:
    style = "waypoint";
    break;
  case kmlpt_multitrack:
    style = "multiTrack";
    break;
  case kmlpt_other:
    style = customstyle;
    force_heading = 1;
    break;
  default:
    fatal("kml_output_point: unknown point type");
    break;
  }

  kml_write_bitmap_style_(style, bitmap, 0, force_heading);
  kml_write_bitmap_style_(style, bitmap, 1, force_heading);

  kml_write_xml(1, "<StyleMap id=\"%s\">\n", style);
  kml_write_xml(1, "<Pair>\n");
  kml_write_xml(0, "<key>normal</key>\n");
  kml_write_xml(0, "<styleUrl>#%s_%c</styleUrl>\n",style, hovertag(0));
  kml_write_xml(-1, "</Pair>\n");
  kml_write_xml(1, "<Pair>\n");
  kml_write_xml(0, "<key>highlight</key>\n");
  kml_write_xml(0, "<styleUrl>#%s_%c</styleUrl>\n",style, hovertag(1));
  kml_write_xml(-1, "</Pair>\n");
  kml_write_xml(-1, "</StyleMap>\n");
}
