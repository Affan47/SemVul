CreateStaticVideoViewElem(const std::string& content_name,
                                            const StaticVideoView& view) {
  buzz::XmlElement* view_elem =
      CreateVideoViewElem(content_name, STR_JINGLE_DRAFT_VIEW_TYPE_STATIC);
  AddXmlAttr(view_elem, QN_SSRC, view.ssrc);

  buzz::XmlElement* params_elem = new buzz::XmlElement(QN_JINGLE_DRAFT_PARAMS);
  AddXmlAttr(params_elem, QN_WIDTH, view.width);
  AddXmlAttr(params_elem, QN_HEIGHT, view.height);
  AddXmlAttr(params_elem, QN_FRAMERATE, view.framerate);
  AddXmlAttr(params_elem, QN_PREFERENCE, view.preference);
  view_elem->AddElement(params_elem);

  return view_elem;
}
