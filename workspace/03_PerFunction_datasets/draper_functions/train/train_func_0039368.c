ParseStaticVideoView(const buzz::XmlElement* view_elem,
                          StaticVideoView* view,
                          ParseError* error) {
  if (!ParseSsrc(view_elem->Attr(QN_SSRC), &(view->ssrc))) {
    return BadParse("Invalid or missing view ssrc.", error);
  }

  const buzz::XmlElement* params_elem =
      view_elem->FirstNamed(QN_JINGLE_DRAFT_PARAMS);
  if (params_elem) {
    view->width = GetXmlAttr(params_elem, QN_WIDTH, 0);
    view->height = GetXmlAttr(params_elem, QN_HEIGHT, 0);
    view->framerate = GetXmlAttr(params_elem, QN_FRAMERATE, 0);
    view->preference = GetXmlAttr(params_elem, QN_PREFERENCE, 0);
  } else {
    return BadParse("Missing view params.", error);
  }

  return true;
}
