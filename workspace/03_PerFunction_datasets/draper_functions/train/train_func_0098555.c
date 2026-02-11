CreateIconStyle(double scale) {
  KmlFactory* kml_factory = KmlFactory::GetFactory();
  IconStyleIconPtr icon = kml_factory->CreateIconStyleIcon();
  icon->set_href(kDotIcon);
  IconStylePtr icon_style = kml_factory->CreateIconStyle();
  icon_style->set_icon(icon);
  icon_style->set_scale(scale);
  return icon_style;
}
