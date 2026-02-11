unparse(ostream &os, ostream_manipulator separator) const
{
  os << "<BLOCKQUOTE>" << separator;
  if (content.get()) foreach(*content, os, separator);
  os << "</BLOCKQUOTE>" << separator;
}
