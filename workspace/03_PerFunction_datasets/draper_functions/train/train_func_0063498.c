FVAutoHintSubs(FontViewBase *fv) {
    int i, cnt=0, gid;

    if ( fv->sf->mm!=NULL && fv->sf->mm->apple )
return;
    for ( i=0; i<fv->map->enccount; ++i )
	if ( fv->selected[i] && (gid = fv->map->map[i])!=-1 &&
		SCWorthOutputting(fv->sf->glyphs[gid]) )
	    ++cnt;
    ff_progress_start_indicator(10,_("Finding Substitution Points..."),_("Finding Substitution Points..."),0,cnt,1);

    for ( i=0; i<fv->map->enccount; ++i ) if ( fv->selected[i] &&
	    (gid = fv->map->map[i])!=-1 && SCWorthOutputting(fv->sf->glyphs[gid]) ) {
	SplineChar *sc = fv->sf->glyphs[gid];
	SCFigureHintMasks(sc,fv->active_layer);
	SCUpdateAll(sc);
	if ( !ff_progress_next())
    break;
    }
    ff_progress_end_indicator();
}
