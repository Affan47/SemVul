xml_write_amount(std::ostream& out, const amount_t& amount,
		      const int depth = 0)
{
  for (int i = 0; i < depth; i++) out << ' ';
  out << "<amount>\n";

  commodity_t& c = amount.commodity();
  for (int i = 0; i < depth + 2; i++) out << ' ';
  out << "<commodity flags=\"";
  if (! (c.flags() & COMMODITY_STYLE_SUFFIXED)) out << 'P';
  if (c.flags() & COMMODITY_STYLE_SEPARATED)    out << 'S';
  if (c.flags() & COMMODITY_STYLE_THOUSANDS)    out << 'T';
  if (c.flags() & COMMODITY_STYLE_EUROPEAN)     out << 'E';
  out << "\">\n";
  for (int i = 0; i < depth + 4; i++) out << ' ';
#if 0

  if (c.price) {
    out << "<symbol>" << c.base->symbol << "</symbol>\n";
    for (int i = 0; i < depth + 4; i++) out << ' ';
    out << "<price>\n";
    xml_write_amount(out, *c.price, depth + 6);
    for (int i = 0; i < depth + 4; i++) out << ' ';
    out << "</price>\n";
  } else {
    out << "<symbol>" << c.symbol << "</symbol>\n";
  }
#endif
  for (int i = 0; i < depth + 2; i++) out << ' ';
  out << "</commodity>\n";

  for (int i = 0; i < depth + 2; i++) out << ' ';
  out << "<quantity>";
  out << amount.quantity_string() << "</quantity>\n";

  for (int i = 0; i < depth; i++) out << ' ';
  out << "</amount>\n";
}
