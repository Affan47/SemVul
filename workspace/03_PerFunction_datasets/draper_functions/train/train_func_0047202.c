ajPhyloStateTrace(const AjPPhyloState thys)
{
    ajint i;

    ajDebug("ajPhyloStateTrace\n");
    ajDebug("=================\n");

    ajDebug("  Len: %d  Size: %d Count: %d Characters: '%S'\n",
	    thys->Len, thys->Size, thys->Count, thys->Characters);

    for(i=0; i < thys->Size; i++)
	ajDebug("%S: %S\n", thys->Names[i], thys->Str[i]);

    return;
}
