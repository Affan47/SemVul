compile(string const &str)
{
  const char *error;
  int erroroffset;
  re = pcre_compile(str.c_str(), PCRE_DOTALL|PCRE_CASELESS|PCRE_EXTENDED|PCRE_UTF8,
	            &error, &erroroffset, NULL);
  if(re == NULL)
  {
    wcerr << L"Error: pcre_compile ";
    cerr << error << endl;
    exit(EXIT_FAILURE);
  }

  empty = false;
}
