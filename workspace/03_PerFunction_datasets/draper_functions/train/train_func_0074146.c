GDrawArabicForms(GBiText *bd, int32 start, int32 end) {
    unichar_t *pt, *last = bd->text+end, *rpt, *alef_pt=NULL;
    int letter_left = false, was_alef=false;


    for ( pt=bd->text+start; pt<last; ++pt ) {
	int ch = *pt;
	if ( ch>=0x600 && ch<=0x6ff && ArabicForms[ch-0x600].isletter ) {
	    if ( !ArabicForms[ch-0x600].joindual ) letter_left = false;
	    for ( rpt = pt+1; rpt<last && *rpt<0x10000 && (iscombining(*rpt) || *rpt==0x200d); ++rpt );
	    if ( rpt==last || *rpt<0x600 || *rpt>0x6ff ||
		    !ArabicForms[*rpt-0x600].isletter ) {
		if ( letter_left )
		    *pt = ArabicForms[ch-0x600].initial;
		else
		    *pt = ArabicForms[ch-0x600].isolated;
	    } else {
		if ( letter_left )
		    *pt = ArabicForms[ch-0x600].medial;
		else
		    *pt = ArabicForms[ch-0x600].final;
	    }
	    if ( was_alef && ch==0x644 ) {

		if ( *pt==0xFEDF  )
		    *alef_pt = 0xfefb;
		else
		    *alef_pt = 0xfefc;
#if 0


		--end; --last;
		for ( i = pt-bd->text; i<end; ++i ) {
		    bd->text[i] = bd->text[i+1];
		    bd->original[i] = bd->original[i+1];

		}
		bd->text[i] = 0x200d;
		--pt;
#else
		*pt = 0x200b;
#endif
	    }
	    if (( was_alef = ch==0x627  ))
		alef_pt = pt;
	    letter_left = true;
	} else if ( ch<0x10000 && !iscombining(ch) && ch!=0x200d )
	    was_alef = letter_left = false;
    }
}
