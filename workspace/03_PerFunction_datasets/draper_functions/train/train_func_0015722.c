compressQuoted(bool stripQuotationMarks)
{
  size_t argLen;
  size_t i;
  std::string myNewArg;

  for (i = 0; i < myArgc; i++)
  {
    argLen = strlen(myArgv[i]);
    if (stripQuotationMarks && argLen >= 2 &&
	myArgv[i][0] == '"' && myArgv[i][argLen - 1] == '"')
    {
      myNewArg = &myArgv[i][1];
      myNewArg[myNewArg.size() - 1] = '\0';
      delete[] myArgv[i];

      myArgv[i] = cppstrdup(myNewArg.c_str());

      continue;
    }

    if (argLen >= 2 && myArgv[i][0] == '"' && myArgv[i][argLen - 1] != '"')
    {


      if (stripQuotationMarks)
	myNewArg = &myArgv[i][1];
      else
	myNewArg = myArgv[i];

      bool isEndQuoteFound = false;


      while ((i + 1 < myArgc) && !isEndQuoteFound) {

        int nextArgLen = strlen(myArgv[i+1]);


        if ((nextArgLen > 0) &&
	    (myArgv[i+1][nextArgLen - 1] == '"'))
	{
	      isEndQuoteFound = true;
        }


        myNewArg += " ";
        myNewArg += myArgv[i+1];

	if (stripQuotationMarks && myNewArg.size() > 0 && isEndQuoteFound)
	  myNewArg[myNewArg.size() - 1] = '\0';

        removeArg(i+1);

        delete[] myArgv[i];


        myArgv[i] = cppstrdup(myNewArg.c_str());

      }
    }
  }
}
