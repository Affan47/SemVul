ClassifyWordSol(unsigned int start, unsigned int end, WordList &keywords, Accessor &styler, char *prevWord)
{
    char s[100] = "";
    bool wordIsNumber = isdigit(styler[start]) != 0;
    for (unsigned int i = 0; i < end - start + 1 && i < 30; i++)
     {
           s[i] = styler[start + i];
           s[i + 1] = '\0';
     }
    char chAttr = SCE_SCRIPTOL_IDENTIFIER;
    if (0 == strcmp(prevWord, "class"))       chAttr = SCE_SCRIPTOL_CLASSNAME;
    else if (wordIsNumber)                    chAttr = SCE_SCRIPTOL_NUMBER;
    else if (keywords.InList(s))              chAttr = SCE_SCRIPTOL_KEYWORD;
    else for (unsigned int i = 0; i < end - start + 1; i++)
    {
        if (styler[start + i] == '.')
        {
            styler.ColourTo(start + i - 1, chAttr);
            styler.ColourTo(start + i, SCE_SCRIPTOL_OPERATOR);
        }
    }
    styler.ColourTo(end, chAttr);
    strcpy(prevWord, s);
}
