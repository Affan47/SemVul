CheckForKeyword(StyleContext& sc, WordList* keywordlists[], int activeState)
{
  int length = sc.LengthCurrent() + 1;
  char* s = new char[length];
  sc.GetCurrentLowered(s, length);
  if (keywordlists[0]->InList(s))
    sc.ChangeState(SCE_MYSQL_MAJORKEYWORD | activeState);
  else
    if (keywordlists[1]->InList(s))
      sc.ChangeState(SCE_MYSQL_KEYWORD | activeState);
    else
      if (keywordlists[2]->InList(s))
        sc.ChangeState(SCE_MYSQL_DATABASEOBJECT | activeState);
      else
        if (keywordlists[3]->InList(s))
          sc.ChangeState(SCE_MYSQL_FUNCTION | activeState);
        else
          if (keywordlists[5]->InList(s))
            sc.ChangeState(SCE_MYSQL_PROCEDUREKEYWORD | activeState);
          else
            if (keywordlists[6]->InList(s))
              sc.ChangeState(SCE_MYSQL_USER1 | activeState);
            else
              if (keywordlists[7]->InList(s))
                sc.ChangeState(SCE_MYSQL_USER2 | activeState);
              else
                if (keywordlists[8]->InList(s))
                  sc.ChangeState(SCE_MYSQL_USER3 | activeState);
  delete [] s;
}
