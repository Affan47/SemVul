next(Token* t) {
    if (input->next(t) == NULL)
      return NULL;

    TCHAR* text = t->termBuffer();
    const int32_t textLength = t->termLength();
    const TCHAR* type = t->type();

    if ( type == tokenImage[APOSTROPHE] &&
		  ( textLength >= 2 && _tcsicmp(text+textLength-2, _T("'s"))==0  ) )
    {

      text[textLength-2]=0;
	    t->resetTermTextLen();

      return t;

    } else if ( type == tokenImage[ACRONYM] ) {
      int32_t j = 0;
      for ( int32_t i=0;i<textLength;i++ ){
        if ( text[i] != '.' )
          text[j++]=text[i];
      }
      text[j]=0;
      t->resetTermTextLen();
      return t;

    } else {
      return t;
    }
  }
