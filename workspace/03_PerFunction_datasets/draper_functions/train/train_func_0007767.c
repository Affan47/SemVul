FoldSolDoc(unsigned int startPos, int length, int initStyle,
						   WordList *[], Accessor &styler)
 {
	int lengthDoc = startPos + length;

	int lineCurrent = styler.GetLine(startPos);
	if (startPos > 0)
        {
          if (lineCurrent > 0)
          {
               lineCurrent--;
               startPos = styler.LineStart(lineCurrent);
               if (startPos == 0)
                    initStyle = SCE_SCRIPTOL_DEFAULT;
               else
                    initStyle = styler.StyleAt(startPos-1);
           }
	}
	int state = initStyle & 31;
	int spaceFlags = 0;
        int indentCurrent = styler.IndentAmount(lineCurrent, &spaceFlags, IsSolComment);
        if (state == SCE_SCRIPTOL_TRIPLE)
             indentCurrent |= SC_FOLDLEVELWHITEFLAG;
	char chNext = styler[startPos];
	for (int i = startPos; i < lengthDoc; i++)
         {
		char ch = chNext;
		chNext = styler.SafeGetCharAt(i + 1);
		int style = styler.StyleAt(i) & 31;

		if ((ch == '\r' && chNext != '\n') || (ch == '\n') || (i == lengthDoc))
                {
                   int lev = indentCurrent;
                   int indentNext = styler.IndentAmount(lineCurrent + 1, &spaceFlags, IsSolComment);
                   if (style == SCE_SCRIPTOL_TRIPLE)
                        indentNext |= SC_FOLDLEVELWHITEFLAG;
                   if (!(indentCurrent & SC_FOLDLEVELWHITEFLAG))
                    {

                        if ((indentCurrent & SC_FOLDLEVELNUMBERMASK) < (indentNext & SC_FOLDLEVELNUMBERMASK))
                        {
                              lev |= SC_FOLDLEVELHEADERFLAG;
                        }
                        else if (indentNext & SC_FOLDLEVELWHITEFLAG)
                        {

                             int spaceFlags2 = 0;
                             int indentNext2 = styler.IndentAmount(lineCurrent + 2, &spaceFlags2, IsSolComment);
                             if ((indentCurrent & SC_FOLDLEVELNUMBERMASK) < (indentNext2 & SC_FOLDLEVELNUMBERMASK))
                             {
                                   lev |= SC_FOLDLEVELHEADERFLAG;
                              }
                        }
                    }
                   indentCurrent = indentNext;
                   styler.SetLevel(lineCurrent, lev);
                   lineCurrent++;
		}
	}
}
