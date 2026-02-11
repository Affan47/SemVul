acdPromptOutdir(AcdPAcd thys)
{
    static ajint count=0;

    const AjPStr knowntype;

    knowntype = acdKnowntypeDesc(thys);

    if(ajStrGetLen(knowntype))
    {
	count++;
	acdPromptStandardS(thys, knowntype);

	if(!ajStrSuffixC(knowntype, " file"))
	    acdPromptStandardAppend(thys, " file");
	acdPromptStandardAppend(thys, " output directory");
    }
    else
	acdPromptStandard(thys, "output directory", &count);

    if(!acdAttrTestDefined(thys, "default") &&
       acdAttrTestDefined(thys, "nullok"))
	acdPromptStandardAppend(thys, " (optional)");

    return thys->StdPrompt;
}
