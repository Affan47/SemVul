suggestWord(UT_GenericVector<UT_UCSChar *> * pVecSuggestions, const UT_UCSChar * pWord, UT_uint32 len)
{


  UT_GenericVector<UT_UCSChar *> * pVec = m_hashWords.enumerate();
  UT_ASSERT(pVec);
  UT_uint32 i=0;
  UT_uint32 count = pVec->getItemCount();


  UT_UCSChar * pszWord = static_cast<UT_UCSChar*>(UT_calloc(len+1, sizeof(UT_UCSChar)));
  for(i=0; i< len; i++)
  {
    pszWord[i] = pWord[i];
  }
  pszWord[len] = 0;


  for(i=0; i< count; i++)
  {
    UT_UCSChar * pszDict = pVec->getNthItem(i);
    UT_UCSChar * pszReturn = NULL;
    float lenDict = static_cast<float>(UT_UCS4_strlen(pszDict));
    UT_uint32 wordInDict = countCommonChars(pszDict,pszWord);
    UT_uint32 dictInWord = countCommonChars(pszWord,pszDict);
    float flen = static_cast<float>(len);
    float frac1 = (static_cast<float>(wordInDict)) / flen;
    float frac2 = (static_cast<float>(dictInWord)) / lenDict;

    if((frac1 > 0.8) && (frac2 > 0.8))
    {
	  UT_UCS4_cloneString(&pszReturn, pszDict);
	  pVecSuggestions->addItem(pszReturn);
    }
  }
  FREEP(pszWord);
  DELETEP(pVec);
}
