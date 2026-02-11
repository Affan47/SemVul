main()
{
  const char * text = "abracadabra";


  SuffixTree<char> t(200);


  std::copy(text, text + strlen(text), std::back_inserter(t));


  PathDump dumper;
  path(t, dumper, text, text + strlen(text));

  return 0;
}
