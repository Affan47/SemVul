collectAttributes() const {
    KWargs atts = FoliaElement::collectAttributes();
    if ( !space ){
      atts["space"] = "no";
    }
    return atts;
  }
