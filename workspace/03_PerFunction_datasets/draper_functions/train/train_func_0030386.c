AutoKernScript(FontViewBase *fv,int spacing, int threshold,
	struct lookup_subtable *sub, char *kernfile) {
    WidthInfo wi;
    SplineFont *sf = fv->sf;

    memset(&wi,'\0',sizeof(wi));
    wi.autokern = 1;
    wi.sf = sf;
    wi.fv = fv;
    AW_FindFontParameters(&wi);
    if ( spacing>-(sf->ascent+sf->descent) )
	wi.spacing = spacing;
    wi.threshold = threshold;
    wi.subtable = sub;

    if ( kernfile==NULL ) {
	wi.left = autowidthBuildCharList(wi.fv, wi.sf, &wi.lcnt, &wi.real_lcnt, &wi.l_Ipos, false );
	wi.right = autowidthBuildCharList(wi.fv, wi.sf, &wi.rcnt, &wi.real_rcnt, &wi.r_Ipos, false );
	if ( wi.lcnt==0 || wi.rcnt==0 ) {
	    AW_FreeCharList(wi.left);
	    AW_FreeCharList(wi.right);
return( false );
	}
	AW_ScriptSerifChecker(&wi);
	AW_InitCharPairs(&wi);
    } else {
	if ( !AW_ReadKernPairFile(copy(kernfile),&wi))
return( false );
    }
    wi.done = true;
    AW_BuildCharPairs(&wi);
    AW_AutoKern(&wi);
    AW_KernRemoveBelowThreshold(wi.sf,KernThreshold(wi.sf,0));
    AW_FreeCharList(wi.left);
    AW_FreeCharList(wi.right);
    AW_FreeCharPairs(wi.pairs,wi.lcnt*wi.rcnt);
return( true );
}
