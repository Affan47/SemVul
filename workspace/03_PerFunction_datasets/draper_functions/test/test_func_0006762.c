getTags(FXStringList & tags) {
  if (xiph)
    xiph_get_field("GENRE",tags);
  else if (id3v2) {
    id3v2_get_field("TCON",tags);
    parse_tagids(tags);
    }
  else if (mp4)
    mp4_get_field("\251gen",tags);
  else if (ape)
    ape_get_field("GENRE",tags);
  else
    tags.append(FXString(tag->genre().toCString(true)));
  }
