add(const char*opt,double&var,const char*desc, bool show_default)
{
  sstring tmp (opt);
  vector<sstring> v = tmp.split();
  if (desc)
    {
      options_help_text << "-" << sstring::join (v,",-") << " <real>\t" << desc;
      if (show_default)
	{
	  char buf[100];
	  sprintf (buf, "%g", var);
	  options_help_text << " (default is " << buf << ")";
	}
      options_help_text << "\n";
    }
  for_contents (vector<sstring>, v, i)
    {
      new_opt (*i);
      double_opts[*i] = &var;
    }
}
