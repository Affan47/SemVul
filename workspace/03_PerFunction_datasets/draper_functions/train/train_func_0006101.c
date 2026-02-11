ReSerifTopStem(SplineChar *sc,int layer,StemInfo *h,ItalicInfo *ii) {
    SplinePoint *start=NULL, *end=NULL;
    SplineSet *ss, *oldss;
    int at_xh = true;

    if ( h==NULL )
return;
    if ( ii->transform_top_xh_serifs )
	FindTopSerifOnStem(sc,layer,h,ii->x_height,ii,&start,&end,&oldss);
    if ( start==NULL && ii->transform_top_as_serifs ) {
	FindTopSerifOnStem(sc,layer,h,ii->ascender_height,ii,&start,&end,&oldss);
	at_xh = false;
    }
    if ( start==NULL || end==NULL || start==end || !IsLeftHalfSerif(start,end,h))
return;
    SerifRemove(start,end,oldss);

    ss = MakeTopItalicSerif(start->me.x-end->me.x,end->me.x,ii,at_xh);
    start = StemMoveTopEndCarefully(start,oldss,ss,NULL,true );
    end   = StemMoveTopEndCarefully(end  ,oldss,ss,NULL,false);

    SplineNextSplice(start,ss->first);
    SplinePrevSplice(end,ss->last);
    chunkfree(ss,sizeof(*ss));
}
