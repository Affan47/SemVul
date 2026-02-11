acdListReport(const char* title)
{
    AcdPAcd pa;

    ajint i = 0;
    ajint j = 0;
    char underline[256];


    if(!acdDoLog)
	return;

    j = strlen(title);
    if(j > 255)
	j = 255;

    memset(underline, '=', j);
    underline[j] = '\0';

    acdLog("\n");
    acdLog("%s\n", title);
    acdLog("%s\n", underline);
    acdLog("\n");

    for(pa=acdList; pa; pa=pa->Next)
    {
	acdLog("ACD %d\n", i);

	if(pa->PNum)
	{
	    acdLog("       Name: '%S[%d]'\n", pa->Name, pa->PNum);
	    acdLog("      Token: '%S[%d]'\n", pa->Token, pa->PNum);
	}
	else
	{
	    acdLog("       Name: '%S'\n", pa->Name);
	    acdLog("      Token: '%S'\n", pa->Token);
	}
	acdLog("      Param: %d\n", pa->PNum);
	acdLog("      Level: %d   (%s)\n", pa->Level, acdLevel[pa->Level]);

	if(acdIsQtype(pa))
	    acdLog("  Qual Type: %d   (%s)\n", pa->Type,
		   acdType[pa->Type].Name);
	else
	    acdLog("   Key Type: %d   (%s)\n", pa->Type,
		   acdKeywords[pa->Type].Name);
	acdLog("      NAttr: %d\n", pa->NAttr);
	acdLog("      Assoc: %B\n", pa->Assoc);

	if(pa->AssocQuals)
	    acdLog(" AssocQuals: %S\n", pa->AssocQuals->Name);
	else
	    acdLog(" AssocQuals: <undefined>\n");
	acdLog("    Defined: %B\n", pa->Defined);
	acdLog("    Userdefined: %B\n", pa->UserDefined);
	acdLog("Orig. Value: '%S'\n", pa->OrigStr);

	if(pa->ValStr)
	    acdLog("      Value: '%S'\n", pa->ValStr);
	else
	    acdLog("      Value: <undefined>\n");
	acdLog("\n");

	if(pa->DefStr)
	{
	    acdLog("      Default Attributes:\n");
	    acdListAttr(acdAttrDef, pa->DefStr, nDefAttr);
	    acdLog("\n");
	}
	acdLog("      Attributes:\n");

	if(acdIsQtype(pa))
	    acdListAttr(acdType[pa->Type].Attr, pa->AttrStr, pa->NAttr);
	else
	    acdListAttr(acdKeywords[pa->Type].Attr, pa->AttrStr, pa->NAttr);

	acdLog("\n");
	i++;
    }

    return;
}
