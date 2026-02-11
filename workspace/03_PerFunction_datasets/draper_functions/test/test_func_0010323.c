FindDefineParm(MACROENTRY *srcParms, MACROENTRY *invParms,
                        char *lookString, unsigned int *recognizedLen, char **invString)
{
    MACROTEXT *srcText;
    MACROTEXT *invText;
    char *checkStr;
    unsigned int checkLen = 0;
    unsigned int sLen;

    checkStr = lookString;
    *invString = NULL;


    checkStr = FindAlphaNum(lookString, &checkLen);

    while (checkStr != NULL)
    {

        srcText = srcParms->firstMacroParms;
        invText = invParms->firstMacroParms;
        while (srcText)
        {
            sLen = strlen(srcText->macroText);

            if (sLen == checkLen)
            {
                if (!strncmp(checkStr, srcText->macroText, checkLen))
                {

                    *invString = invText->macroText;

                    *recognizedLen = checkLen;
                    return checkStr;
                }
            }

            srcText = srcText->next;
            invText = invText->next;
        }


        checkStr = FindAlphaNum(checkStr+checkLen, &checkLen);
    }

    return NULL;
}
