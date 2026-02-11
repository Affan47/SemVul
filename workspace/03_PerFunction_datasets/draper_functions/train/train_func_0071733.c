get_next_word()
{
  if(vwords.size() != 0)
  {
    TaggerWord* word=vwords.front();
    vwords.erase(vwords.begin());

    return word;
  }

  if(feof(input))
  {
    return NULL;
  }

  int ivwords = 0;
  vwords.push_back(new TaggerWord());

  while(true)
  {
    int symbol = fgetwc_unlocked(input);
    if(feof(input))
    {
      vwords[ivwords]->add_tag(ca_tag_keof, L"", td->getPreferRules());
      return get_next_word();
    }
    if(symbol == L'^')
    {
      readRestOfWord(ivwords);
      return get_next_word();
    }
    else
    {
      wstring str = L"";
      if(symbol == L'\\')
      {
        symbol = fgetwc_unlocked(input);
        str += L'\\';
        str += static_cast<wchar_t>(symbol);
        symbol = L'\\';
      }
      else
      {
        str += static_cast<wchar_t>(symbol);
      }

      while(symbol != L'^')
      {
	symbol = fgetwc_unlocked(input);
	if(feof(input))
	{
	  vwords[ivwords]->add_ignored_string(str);
          vwords[ivwords]->add_tag(ca_tag_keof, L"", td->getPreferRules());
	  return get_next_word();
	}
	else if(symbol == L'\\')
	{
	  str += L'\\';
          symbol = fgetwc_unlocked(input);
	  if(feof(input))
	  {
	    vwords[ivwords]->add_ignored_string(str);
            vwords[ivwords]->add_tag(ca_tag_keof, L"", td->getPreferRules());
	    return get_next_word();
	  }
	  str += static_cast<wchar_t>(symbol);
	  symbol = L'\\';
	}
	else if(symbol == L'^')
	{
	  if(str.size() > 0)
	  {
	    vwords[ivwords]->add_ignored_string(str);
          }
	  readRestOfWord(ivwords);
	  return get_next_word();
	}
        else
	{
	  str += static_cast<wchar_t>(symbol);
	}
      }
    }
  }
}
