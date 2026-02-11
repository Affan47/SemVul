lex_state_to_str(int state)
{
   switch (state) {
   case lex_none:          return _("none");
   case lex_comment:       return _("comment");
   case lex_number:        return _("number");
   case lex_ip_addr:       return _("ip_addr");
   case lex_identifier:    return _("identifier");
   case lex_string:        return _("string");
   case lex_quoted_string: return _("quoted_string");
   case lex_include:       return _("include");
   case lex_include_quoted_string: return _("include_quoted_string");
   case lex_utf8_bom:      return _("UTF-8 Byte Order Mark");
   case lex_utf16_le_bom:  return _("UTF-16le Byte Order Mark");
   default:                return "??????";
   }
}
