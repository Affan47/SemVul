amdlibSetInsCfgKeyword(amdlibINS_CFG   *insCfg,
                                        char            *keywName,
                                        char            *keywVal,
                                        char            *keywCmt,
                                        amdlibERROR_MSG errMsg)
{
    int i;
    char name[amdlibKEYW_NAME_LEN+1];
    char currentName[amdlibKEYW_NAME_LEN+1];

    strcpy(name, keywName);
    amdlibStripBlanks(name);


    for (i = 0; i < insCfg->nbKeywords; i++)
    {
        strcpy(currentName, insCfg->keywords[i].name);
        amdlibStripBlanks(currentName);

        if (strcmp(name, currentName) == 0)
        {
            memset(insCfg->keywords[i].value, '\0',
                   sizeof(char[amdlibKEYW_VAL_LEN+1]));
            memset(insCfg->keywords[i].comment, '\0',
                   sizeof(char[amdlibKEYW_CMT_LEN+1]));
            strcpy(insCfg->keywords[i].value, keywVal);
            strcpy(insCfg->keywords[i].comment, keywCmt);
            return amdlibSUCCESS;
        }
    }

    if (i < amdlibNB_INS_CFG_KEYW)
    {
        strcpy(insCfg->keywords[i].name, keywName);
        strcpy(insCfg->keywords[i].value, keywVal);
        if (keywCmt != NULL || strlen(keywCmt) != 0)
        {
            strcpy(insCfg->keywords[i].comment, keywCmt);
        }
        insCfg->nbKeywords++;
        return amdlibSUCCESS;
    }

    amdlibSetErrMsg("insCfg array is full - impossible to insert %s", keywName);
    return amdlibFAILURE;
}
