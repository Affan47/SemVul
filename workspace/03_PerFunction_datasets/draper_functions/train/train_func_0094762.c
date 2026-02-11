FcFreeTypeLangSet (const FcCharSet  *charset,
		   const FcChar8    *exclusiveLang)
{
    int		    i, j;
    FcChar32	    missing;
    const FcCharSet *exclusiveCharset = 0;
    FcLangSet	    *ls;

    if (exclusiveLang)
	exclusiveCharset = FcLangGetCharSet (exclusiveLang);
    ls = FcLangSetCreate ();
    if (!ls)
	return 0;
    if (FcDebug() & FC_DBG_LANGSET)
    {
	printf ("font charset");
	FcCharSetPrint (charset);
	printf ("\n");
    }
    for (i = 0; i < NUM_LANG_CHAR_SET; i++)
    {
	if (FcDebug() & FC_DBG_LANGSET)
	{
	    printf ("%s charset", fcLangCharSets[i].lang);
	    FcCharSetPrint (&fcLangCharSets[i].charset);
	    printf ("\n");
	}


	if (exclusiveCharset &&
	    FcFreeTypeIsExclusiveLang (fcLangCharSets[i].lang))
	{
	    if (fcLangCharSets[i].charset.num != exclusiveCharset->num)
		continue;

	    for (j = 0; j < fcLangCharSets[i].charset.num; j++)
		if (FcCharSetLeaf(&fcLangCharSets[i].charset, j) !=
		    FcCharSetLeaf(exclusiveCharset, j))
		    continue;
	}
	missing = FcCharSetSubtractCount (&fcLangCharSets[i].charset, charset);
        if (FcDebug() & FC_DBG_SCANV)
	{
	    if (missing && missing < 10)
	    {
		FcCharSet   *missed = FcCharSetSubtract (&fcLangCharSets[i].charset,
							 charset);
		FcChar32    ucs4;
		FcChar32    map[FC_CHARSET_MAP_SIZE];
		FcChar32    next;

		printf ("\n%s(%u) ", fcLangCharSets[i].lang, missing);
		printf ("{");
		for (ucs4 = FcCharSetFirstPage (missed, map, &next);
		     ucs4 != FC_CHARSET_DONE;
		     ucs4 = FcCharSetNextPage (missed, map, &next))
		{
		    int	    i, j;
		    for (i = 0; i < FC_CHARSET_MAP_SIZE; i++)
			if (map[i])
			{
			    for (j = 0; j < 32; j++)
				if (map[i] & (1 << j))
				    printf (" %04x", ucs4 + i * 32 + j);
			}
		}
		printf (" }\n\t");
		FcCharSetDestroy (missed);
	    }
	    else
		printf ("%s(%u) ", fcLangCharSets[i].lang, missing);
	}
	if (!missing)
	    FcLangSetBitSet (ls, i);
    }

    if (FcDebug() & FC_DBG_SCANV)
	printf ("\n");


    return ls;
}
