procWord(FILE *input, FILE *output)
{
  int mychar;
  wstring buffer = L"";

  bool buffer_mode = false;
  while((mychar = fgetwc_unlocked(input)) != L'$')
  {
    if(feof(input))
    {
      wcerr << L"ERROR: Unexpected EOF" << endl;
      exit(EXIT_FAILURE);
    }

    switch(mychar)
    {
    case L'<':
      if(!buffer_mode)
      {
	buffer_mode = true;
      }
      break;
    case L'#':
      if(buffer_mode)
      {
	buffer_mode = false;
      }
      break;
    }

    if(buffer_mode)
    {
      if(mychar != L'+')
      {
	buffer += static_cast<wchar_t>(mychar);
      }
      else
      {
        buffer.append(L"$ ^");
      }
    }
    else
    {
      fputwc_unlocked(mychar, output);
    }
  }
  fputws_unlocked(buffer.c_str(), output);
}
