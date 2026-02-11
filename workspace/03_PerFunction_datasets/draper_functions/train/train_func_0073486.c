applyRule()
{
  unsigned int limit = tmpword.size();

  for(unsigned int i = 0; i != limit; i++)
  {
    if(i == 0)
    {
      word = new TransferWord *[limit];
      lword = limit;
      if(limit != 1)
      {
        blank = new string *[limit - 1];
        lblank = limit - 1;
      }
      else
      {
        blank = NULL;
        lblank = 0;
      }
    }
    else
    {
      blank[i-1] = new string(UtfConverter::toUtf8(*tmpblank[i-1]));
    }

    pair<wstring, int> tr;
    if(useBilingual)
    {
      tr = fstp.biltransWithQueue(*tmpword[i], false);
    }
    else
    {
      tr = pair<wstring, int>(*tmpword[i], false);
    }

    word[i] = new TransferWord(UtfConverter::toUtf8(*tmpword[i]),
			       UtfConverter::toUtf8(tr.first), tr.second);
  }

  processRule(lastrule);
  lastrule = NULL;

  if(word)
  {
    for(unsigned int i = 0; i != limit; i++)
    {
      delete word[i];
    }
    delete word;
  }
  if(blank)
  {
    for(unsigned int i = 0; i != limit - 1; i++)
    {
      delete blank[i];
    }
    delete blank;
  }
  word = NULL;
  blank = NULL;
  tmpword.clear();
  tmpblank.clear();
  ms.init(me->getInitial());
}
