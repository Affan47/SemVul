CreatePair(int style_state, double icon_scale) {
  KmlFactory* kml_factory = KmlFactory::GetFactory();
  PairPtr pair = kml_factory->CreatePair();
  pair->set_key(style_state);
  StylePtr style = kml_factory->CreateStyle();
  style->set_iconstyle(CreateIconStyle(icon_scale));

  style->set_labelstyle(CreateLabelStyle(
      style_state == kmldom::STYLESTATE_NORMAL ? 0 : 1 ));
  pair->set_styleselector(style);
  return pair;
}
