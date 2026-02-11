make_scope_name(const hname_t&name)
{
      if (! name.has_number())
	    return name.peek_name();

      char buf[1024];
      snprintf(buf, sizeof buf, "%s[%d]",
	       name.peek_name().str(), name.peek_number());
      return lex_strings.make(buf);
}
