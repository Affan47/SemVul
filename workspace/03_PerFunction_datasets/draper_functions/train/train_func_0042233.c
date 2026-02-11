countCommonChars( UT_UCSChar *pszHaystack,UT_UCSChar * pszNeedle)
{
    UT_uint32 lenNeedle =  UT_UCS4_strlen(pszNeedle);
    UT_UCSChar oneChar[2];
    oneChar[1] = 0;
    UT_uint32 i=0;
    UT_uint32 score =0;
    for(i=0; i< lenNeedle; i++)
    {
      oneChar[0] = pszNeedle[i];
      if(UT_UCS4_strstr(pszHaystack,oneChar) != 0)
      {
	  score++;
      }
    }
    return score;
}
