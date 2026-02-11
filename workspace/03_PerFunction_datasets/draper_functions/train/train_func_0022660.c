saveAsXml(Stream &stream, String layer) const
{
  stream << "<text";
  saveAttributesAsXml(stream, layer);
  stream << " pos=\"" << iPos.x << " " << iPos.y << "\"";
  stream << " stroke=\"" << iStroke.string() << "\"";
  switch (iType) {
  case ELabel:
    stream << " type=\"label\"";
    break;
  case EMinipage:
    stream << " type=\"minipage\"";
    break;
  }
  if (iXForm || isMinipage())
    stream << " width=\"" << iWidth << "\"";
  if (iXForm)
    stream << " height=\"" << iHeight << "\""
	   << " depth=\"" << iDepth << "\"";
  saveAlignment(stream, iHorizontalAlignment, iVerticalAlignment);
  if (iSize != Attribute::NORMAL())
    stream << " size=\"" << iSize.string() << "\"";
  if (iStyle != Attribute::NORMAL())
    stream << " style=\"" << iStyle.string() << "\"";
  if (iOpacity != Attribute::OPAQUE())
    stream << " opacity=\"" << iOpacity.string() << "\"";
  stream << ">";
  stream.putXmlString(iText);
  stream << "</text>\n";
}
