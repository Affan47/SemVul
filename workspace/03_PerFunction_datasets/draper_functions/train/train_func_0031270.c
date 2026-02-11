initHiScores(const char * const defaultNames[kHiScoresNumber])
{
    char HSID[8];

    for (int i=0; i<kHiScoresNumber; i++)
    {
        sprintf(HSID,"HSN%2d",i);
        GetStrPreference(HSID,HS[i].name,defaultNames[kHiScoresNumber-i-1],kHiScoreNameLenght+1);
        sprintf(HSID,"HSS%2d",i);
        HS[i].score = GetIntPreference(HSID,(kHiScoresNumber-i) * 10000);
    }
    loaded = true;
}
