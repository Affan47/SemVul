add(const char*opt,sstring&var,const char*desc, bool show_default)
{
  sstring tmp (opt);
  vector<sstring> v = tmp.split();
  if (desc)
    {
      options_help_text << "-" << sstring::join (v,",-") << " <string>\t" << desc;
      if (show_default) options_help_text << " (default is \"" << var << "\")";
      options_help_text << "\n";
    }
  for_contents (vector<sstring>, v, i)
    {
      new_opt (*i);
      string_opts[*i] = &var;
    }
}
