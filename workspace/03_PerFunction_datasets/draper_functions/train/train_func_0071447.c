readDeal(FILE *fileptr)
{
  fp = fileptr;

  reset();

  for(;;)
  { if(readLine() == false)
      return false;
    while(isspace(*pch))
      pch++;
    if(*pch == '{')
    { if(pszComment[0] == '\0')
      { if(readComment() == false)
          return false;
        if(getOptions() == false)
          return false;
      }
      else
      { sprintf(szErrMsg,"*** error: more than one comment at line %d\n",nLine);
        return false;
      }
    }
    else if(*pch == '\0')
    {
      continue;
    }
    else
    {
      break;
    }
  }

  pch = strchr(szLine,':');
  if(pch)
    *pch = '\0';
  strcpy(szDeal,szLine);
  if(pch)
  { pch++;
    if(strlen(pch) != 20)
    { sprintf(szErrMsg,"*** error: length tricks not 20 at line %d\n",
              nLine);
      return false;
    }
    strcpy(szTricks,pch);
  }

  return true;

}
