RequireXmlAttr(const buzz::XmlElement* elem,
                    const buzz::QName& name,
                    std::string* value,
                    ParseError* error) {
  if (!elem->HasAttr(name)) {
    return BadParse("element '" + elem->Name().Merged() +
                    "' missing required attribute '"
                    + name.Merged() + "'",
                    error);
  } else {
    *value = elem->Attr(name);
    return true;
  }
}
